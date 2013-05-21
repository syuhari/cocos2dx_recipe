<?php

$recipes = file_get_contents("./recipes.csv");
$recipes = explode("\n", $recipes);

$plists = array();
$plists[] = '<?xml version="1.0" encoding="UTF-8"?>';
$plists[] = '<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">';
$plists[] = '<plist version="1.0">';
$plists[] = '<array>';

$recipe_no = 1;
foreach ($recipes as $recipe) {
    $plists[] = '<dict>';
    $plists[] = '<key>recipe</key>';
    $plists[] = '<integer>'.$recipe_no++.'</integer>';
    $plists[] = '<key>name</key>';
    $plists[] = '<string>'.$recipe.'</string>';
    $plists[] = '</dict>';
}

$plists[] = '</array>';
$plists[] = '</plist>';

$plist = implode("\n", $plists);
debug($plist);
file_put_contents("./recipes.plist", $plist);

function debug($var) {
    var_dump($var);
}