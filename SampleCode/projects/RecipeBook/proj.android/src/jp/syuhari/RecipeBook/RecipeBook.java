/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package jp.syuhari.RecipeBook;

import java.io.ByteArrayOutputStream;
import java.util.Timer;
import java.util.TimerTask;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.app.Activity;
import android.app.ActivityManager;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.graphics.Bitmap;
import android.graphics.Bitmap.CompressFormat;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.hardware.Camera;
import android.hardware.Camera.PictureCallback;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.KeyEvent;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;
import android.widget.TextView;

public class RecipeBook extends Cocos2dxActivity implements PictureCallback{

	public static String sAppVersion = "";
	private static Handler sHandler;
    private static CameraPreview mPreview = null;

    public static native void nativeMyKeyDown(int KeyCode);
	private static native void nativeDidTakenPhoto(final int size, final byte[] pPixels);
    private Timer mDebugTimer = null;
	
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	

		PackageManager pkgrMgr = super.getContext().getPackageManager();
		try {
			PackageInfo packageInfo = pkgrMgr.getPackageInfo("jp.syuhari.RecipeBook", PackageManager.GET_META_DATA);
			sAppVersion = packageInfo.versionName;
		} catch (NameNotFoundException e) {
			sAppVersion = "unknown";
		}
		
		RecipeBook.sHandler = new Handler() {
			@Override
			public void handleMessage(final Message msg) {
				switch (msg.what) {
					case 1:
						if(mPreview == null){
                            // カメラビューを追加する
							mPreview = new CameraPreview(RecipeBook.this);
							mPreview.setZOrderOnTop(true);
							mPreview.setPictureCallback(RecipeBook.this);
							FrameLayout contentView = (FrameLayout)RecipeBook.this.findViewById(android.R.id.content);
							contentView.addView(mPreview);
						}
						break;
				}
			}
		};
		
		if (BuildConfig.DEBUG) {
			// ContentView に RelativeLayout追加
			FrameLayout contentView = (FrameLayout) this.findViewById(android.R.id.content);
			ViewGroup.LayoutParams relativelayout_params = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.FILL_PARENT, ViewGroup.LayoutParams.FILL_PARENT);
			RelativeLayout relative = new RelativeLayout(this);
			relative.setLayoutParams(relativelayout_params);
			contentView.addView(relative);

			// Debug表示用のView追加
			TextView textView = new TextView(this);
			textView.setBackgroundColor(Color.argb(255/4, 0, 0, 0));
			textView.setSingleLine(false);
			textView.setTextColor(Color.WHITE);
	    	LayoutParams lp = new LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
	    	lp.addRule(RelativeLayout.ALIGN_LEFT, RelativeLayout.TRUE);
	    	lp.addRule(RelativeLayout.ALIGN_TOP, RelativeLayout.TRUE);
	    	relative.addView(textView, lp);

	    	// タイマーでメモリ使用状況表示
	    	mDebugTimer = new Timer(true);
	    	mDebugTimer.schedule(new MemoryStatusTimerTask(textView), 1000, 1000);
		}

    }

    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// RecipeBook should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }

    static {
        System.loadLibrary("cocos2dcpp");
    }     

    public static String getAppVersion() {
        return sAppVersion;
    }

    @Override
    public boolean dispatchKeyEvent(KeyEvent e) {
        final int keycode = e.getKeyCode();
        if (e.getAction() == KeyEvent.ACTION_DOWN) {
            // GLSurfaceViewのスレッドでキーイベントをあげる
            super.runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    // C++の関数 nativeMyKeyDown() を呼び出す
                    nativeMyKeyDown(keycode);
                }
            });
        }
        return super.dispatchKeyEvent(e);
    }

	public static void launchCamera() {
		final Message msg = new Message();
		msg.what = 1;
		RecipeBook.sHandler.sendMessage(msg);
	}
	
	public void onPictureTaken(byte[] data, Camera camera) {
        // 画像を1/8にスケール
    	BitmapFactory.Options options = new BitmapFactory.Options();  
        options.inSampleSize = 8;  
        Bitmap bitmap = BitmapFactory.decodeByteArray(data, 0, data.length, options);
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        bitmap.compress(CompressFormat.PNG, 0 , bos);
        final byte[] bitmapdata = bos.toByteArray();

        // カメラビューを削除
		FrameLayout contentView = (FrameLayout)RecipeBook.this.findViewById(android.R.id.content);
		contentView.removeView(mPreview);
		mPreview = null;

        super.runOnGLThread(new Runnable() {
     	   @Override
     	   public void run() {
               // C++に画像データを通知
               nativeDidTakenPhoto(bitmapdata.length, bitmapdata);
     	   }
        });
		
	}
	private class MemoryStatusTimerTask extends TimerTask {
		private Handler handler;
		private TextView textView;
		   
		public MemoryStatusTimerTask(TextView textView) {
		    handler = new Handler();
		    this.textView = textView;
		}
		
		@Override
		public void run() {
		    handler.post(new Runnable() {
		    	@Override
		        public void run() {
					long allocated = android.os.Debug.getNativeHeapAllocatedSize()/1024;
					long available = android.os.Debug.getNativeHeapSize()/1024;
					long free = android.os.Debug.getNativeHeapFreeSize()/1024;
					long d_free = Runtime.getRuntime().freeMemory()/1024;
					long d_total = Runtime.getRuntime().totalMemory()/1024;

					ActivityManager am = ((ActivityManager)getSystemService(Activity.ACTIVITY_SERVICE));
					ActivityManager.MemoryInfo info = new ActivityManager.MemoryInfo();
					am.getMemoryInfo(info);
					long l_avail = info.availMem / 1024;
					long l_threshold = info.threshold / 1024;
          		
					textView.setText( String.format("native:%,7d of %,7d kb (%,7d free) \ndalvik:%,7d of %,7d kb (%,7d free)\nlinux avail:%,7d th:%,7d low:%b", 
                		allocated, available, free, d_total-d_free, d_total, d_free, l_avail, l_threshold, info.lowMemory));
		    	  
		        }
		    });
		}
	}
}
