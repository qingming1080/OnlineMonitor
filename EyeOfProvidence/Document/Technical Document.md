*Technical Spec*
### 1. Suppress Unused warning in Qt
There is the macro named Q_UNUSED, as following...
```cpp
void myFunction(int value)
{
    Q_UNUSED(value)
    // ...函数体没有用到value，但不会有警告
}
```
### 2. Update Language Package
#### 2.1. Generate/ Update .ts files
```bash
lupdate your.pro
```
```bash
C:\Qt\5.15.17\mingw81_64\bin\lupdate.exe .\ProvidenceEE.pro    
```
#### 2.2. Edit .ts file using Qt Linguist
```bash
linguist SimplifiedChinese.ts
```
```bash
C:\Qt\5.15.17\mingw81_64\bin\linguist .\languageTranslation\SimplifiedChinese.ts

C:\Qt\5.15.17\mingw81_64\bin\linguist .\languageTranslation\English.ts

C:\Users\jerry\software\tools\QT\5.15.12\mingw81_64\bin\linguist.exe .\EyeOfProvidence\languageTranslation\SimplifiedChinese.ts
C:\Users\jerry\software\tools\QT\5.15.12\mingw81_64\bin\lignusit .\languageTranslation\English.ts
```
#### 2.3. Save and Generate .qm files
```bash
lrelease your.pro
```
```bash
C:\Qt\5.15.17\mingw81_64\bin\lrelease.exe .\ProvidenceEE.pro   
```
### 3. New Requirements
#### 3.1 Need to show Samples on Learning Screen
#### 3.2 Backend Learning in case of the parameters adjustment. 
If there are some setting parameters with litter adjustment following the current specific application required, the change shall be detected by system automatically and The system shall be able to decide if the system can go to learning backend parallel with production or run the learning to do learning screen compulsively due to the range of the parameters changes.
#### 3.3 There shall be a new learning tab added in the header so the operator can go to learning directly through this tab.
#### 3.4 Need to add the graph curve screen following the single production.
#### 3.5 The screen shall go to Learning screen automatically when the paramter setting is changed for a new application. The screen can go back to the production screen once the learning process completed.
#### 3.6 Add the refresh button in the card of configuration to reconnect the TCP/IP link when there is any abnormal is deteced.



