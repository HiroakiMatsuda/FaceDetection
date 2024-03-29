FaceDetection
======================
OpenCVの顔検出機能をラップしたRTCです．  
検出した顔のUV座標を出力します．  
[cv]:http://opencv.jp/cookbook/opencv_img.html#id40

動作環境
------
**OS:**  
Windows 7 32bit/64bit  
Windows 8 32bit/64bit  
Ubuntu12.04 LTS 32bit  

**RT-Middleware:**  
[OpenRTM-aist C++ 1.1.0-RC1][py]  
[py]:http://openrtm.org/openrtm/ja/node/4526

**OpenCV**  
動作確認:[OpenCV 2.4.6][cv2]
[cv2]:http://opencv.org/

ファイル構成
------

ファイル構成について，一部抜粋で説明します．  

FaceDetection   
│―FaceDetection\_Linux  
│  　　　│―.project    
│  　　　│―copyprops.bat    
│  　　　│―FaceDetection.conf    
│  　　　│―FaceDetection.cpp    
│  　　　│―FaceDetection.h    
│  　　　│―FaceDetection.o    
│  　　　│―FaceDetection.so    
│  　　　│―FaceDetectionComp    
│  　　　│―FaceDetectionComp.cpp    
│  　　　│―FaceDetectionComp.o    
│  　　　│―Makefile.FaceDetection    
│  　　　│―README.FaceDetection      
│  　　　│―rtc.conf    
│  　　　│―RTC.xml    
│    
│   
│―FaceDetection\_Windows  
│  　　　│―cmake     
│  　　　│―doc    
│  　　　│―idl    
│  　　　│―include    
│  　　　│―src    
│  　　　│　　│―CMakeLists.txt  
│  　　　│　　│―FaceDetection.cpp  
│  　　　│　　│―FaceDetectionComp.cpp  
│  　　　│  
│  　　　│―project    
│  　　　│―CMakeLists.txt    
│  　　　│―COPYING    
│  　　　│―COPYING.LESSER    
│  　　　│―FaceDetection.conf    
│  　　　│―README.FaceDetection     
│  　　　│―rtc.conf   
│  　　　│―RTC.xml    
│    
│    
│―README.md    
│―TestRTC    
　　　　　│―PyPoint2dConsoleOut  

* FaceDetection\_Windows    
Windows OS用のファイルです．  
Windows OSをお使いの方はこのフォルダ内のファイルを使用してください．   

* FaceDetection\_Linux    
Linux OS用のファイルです．ファイル構成はWindows OS用と同様です．  
Linux OSをお使いの方はこのディレクトリ内のファイルを使用してください．     
  
* FaceDetection.cpp  
顔検出のコードをはじめとしたRTCの振る舞いが記述されています．  
RTCを改良する場合はこのファイルを編集してください．  

* Makefile.FaceDetection  
Linux OSでコンパイルするのに必要なファイルです．  
このmakeファイルはpkg-configを使用します．  
下記コマンドの結果インクルードファイルなどが表示されるか確認してください．  
$ pkg-config opencv --cflags  
$ pkg-config opencv --libs  
makeコマンドは以下のように行います．  
$ make -f Makefile.FaceDetection  
環境設定方法がわからない場合は[ここ][vr]を参考にしてください．


* CMakeLists.txt  
Windows OS用のファイルです．  
CMakeを行い，Visual Studio 2010用のソリューションファイルを作成してください．  
その後ソリューションファイルにOpenCV用の環境設定を施します．  
CMakeの使い方や環境設定の方法がわからない場合は，[ここ][vr]を参考にしてください．  
補足：Linux環境でもCMakeを使用してファイルを作成できます．  
その場合はCMakeLists.txtを編集し，OpenCVへのリンクを張ってください．    
  
* TestRTC   
本RTCの動作確認をするためのTest用RTCが収められています．

[vr]:http://hmatsudaiac.wix.com/venus-robotix#!learning/ca4p


RTCの構成
------  
<img src="http://farm3.staticflickr.com/2887/11307423463_3f6253b4c2_o.png" width="300px" />    
データポートは以下のようになっています  

* face_point port :OutPort  
データ型; TimedPoint2d  
 ・double x: 検出した顔の中心座標(u, v)のuを出力します．  
 ・double y: 検出した顔の中心座標(u, v)のvを出力します．  
  
使い方
------

###1. ネームサーバーの起動###
ネームサーバーを起動します．  

Windows:  
Start Naming Serviceで起動します．  
Linux:  
以下のコマンドで起動します．2809はポート番号で任意で選んで構いません．  
$ rtm-naming 2809

###3. RTCの起動###
1. FaceDetectionを起動し，分類器カスケードのファイルパスを設定します．  
・FaceDetectionを起動します．  
Windows:  
FaceDetectionComp.exeをダブルクリックで起動します．    
Linux:  
以下のコマンドで起動します．  
$ ./FaceDetectionComp  
・次に，分類器カスケード haarcascade\_frontalface\_alt.xmlのファイルパスを設定します．  
Windows:   
例：C:\opencv2.4.6\data\haarcascades\haarcascade\_frontalface\_alt.xml    
Linux:   
例： /usr/local/share/OpenCV/haarcascades/haarcascade\_frontalface\_alt.xml  
<img src="http://farm3.staticflickr.com/2819/11307339893_46dcb9553e_o.png" width="500px" />    

2. PyAcceleration3dConsoleOut.pyを起動します．  
Windows:  
FaceDetectionComp.exeをダブルクリックで起動します．  
Linux:  
以下のコマンドで起動します．  
$ python PyAcceleration3dConsoleOut.py  

3. PyPoint2dConsoleOut.pyを起動します．  
Windows:  
PyPoint2dConsoleOut.pyをダブルクリックで起動します．  
Linux:  
以下のコマンドで起動します．  
$ python PyPoint2dConsoleOut.py  

4. RTCの接続
RT System Editorを使用して，FaceDetectionとPyPoint2dConsoleOutを接続します．  
<img src="http://farm8.staticflickr.com/7352/11307291894_0394c6759e_o.png" width="500px" />    


###4. 顔検出の確認###
全てのRTCをActivateし，顔の中心に円が描かれ，中心座標がコンソールに表示されることを確認してください．  
今回読み込んだ分類器カスケードは正面に向いている顔を検出します．  

FaceDetectionのカメラ画面  
注意：この画像はプライバシー保護のため，目付近にモザイク処理を行っています．  
<img src="http://farm8.staticflickr.com/7367/11307409473_766db1dc41_o.png" width="400px" />    

FaceDetectionの実行画面  
<img src="http://farm4.staticflickr.com/3766/11307223855_fe9f25a9a7_o.png" width="400px" />    

PyPoint2dConsoleOutの実行画面  
<img src="http://farm6.staticflickr.com/5487/11307223775_30eb958cce_o.png" width="400px" />    

以上が本RTCの使い方となります．  

LICENSE
----------
Copyright © 2013 Hiroaki Matsuda  

Licensed under the [Apache License, Version 2.0][Apache].  
Distributed under the [MIT License][MIT].  
Dual licensed under the [MIT License][MIT] and [Apache License, Version 2.0][Apache].   
 
[Apache]: http://www.apache.org/licenses/LICENSE-2.0
[MIT]: http://www.opensource.org/licenses/mit-license.php