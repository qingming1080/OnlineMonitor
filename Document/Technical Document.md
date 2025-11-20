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
```
#### 2.3. Save and Generate .qm files
```bash
lrelease your.pro
```
```bash
C:\Qt\5.15.17\mingw81_64\bin\lrelease.exe .\ProvidenceEE.pro   
```
