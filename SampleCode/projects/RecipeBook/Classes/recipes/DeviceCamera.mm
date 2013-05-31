//
//  DeviceCamera.mm
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/31.
//
//

#include "DeviceCamera.h"
#import "AppController.h"

// iOSカメラ宣言
@interface DeviceCameraObjc : NSObject<UINavigationControllerDelegate, UIImagePickerControllerDelegate>
- (BOOL)launchCameraObjc;
+ (DeviceCameraObjc *)sharedInstance;
@end

// iOSカメラ実装
@implementation DeviceCameraObjc

+ (DeviceCameraObjc *)sharedInstance {
    static dispatch_once_t pred = 0;
    static DeviceCameraObjc* _sharedObject = nil;
    dispatch_once(&pred, ^{
        _sharedObject = [[DeviceCameraObjc alloc] init];
    });
    return _sharedObject;
}

- (UIViewController*)rootViewController {
    AppController* appDelegate = (AppController*)[[UIApplication sharedApplication] delegate];
    return (UIViewController*)appDelegate.rootViewController;
}

- (BOOL)launchCameraObjc {
    if(![UIImagePickerController isSourceTypeAvailable:
         UIImagePickerControllerSourceTypeCamera]) {
        return FALSE;
    }
    // カメラを起動
    UIImagePickerController *ipc =
    [[UIImagePickerController alloc] init];
    [ipc setSourceType:UIImagePickerControllerSourceTypeCamera];
    [ipc setAllowsEditing:NO];
    [ipc setDelegate:self];
    
    [[self rootViewController] presentViewController:ipc
                                            animated:YES completion:nil];
    return TRUE;
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker {
    [picker dismissViewControllerAnimated:YES completion:nil];
}

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info {
    
    [picker dismissViewControllerAnimated:YES completion:nil];
    
    // 画像を1/8に縮小
    UIImage *orgImage =
    [info objectForKey:UIImagePickerControllerOriginalImage];
    CGSize toSize = { orgImage.size.width/8, orgImage.size.height/8 };
    UIGraphicsBeginImageContext(toSize);
    CGRect rect = CGRectMake(0, 0, toSize.width, toSize.height);
    [orgImage drawInRect:rect];
    UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    NSData *data = UIImagePNGRepresentation(image);
    
    // 画像をCCTexture2Dにしてデリゲートで通知する
    cocos2d::CCImage *ccImage = new cocos2d::CCImage();
    if (ccImage->initWithImageData(
                                   (void*)[data bytes], [data length])) {
        cocos2d::CCTexture2D *ccTexture = new cocos2d::CCTexture2D();
        if (ccTexture->initWithImage(ccImage)) {
            DeviceCamera* cam = DeviceCamera::sharedInstance();
            cam->didTakePhoto(ccTexture);
        }
        CC_SAFE_RELEASE(ccTexture);
    }
    CC_SAFE_RELEASE(ccImage);
}
@end

DeviceCamera* DeviceCamera::instance = NULL;

DeviceCamera* DeviceCamera::sharedInstance()
{
    if (instance == NULL)
    {
        instance = new DeviceCamera();
    }
    return instance;
}

void DeviceCamera::launchCamera()
{
    DeviceCameraObjc* cameraObj = [DeviceCameraObjc sharedInstance];
    [cameraObj launchCameraObjc];
}

void DeviceCamera::didTakePhoto(cocos2d::CCTexture2D *texture)
{
    if (m_delegate)
    {
        m_delegate->onDeviceCameraDidFinishPick(texture);
    }
}
