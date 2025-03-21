#include <jni.h>
#include <android/log.h>
#include "universe.h"
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <iomanip> 
#include <sstream>
#include <array>
#include <filesystem>
#include <android/log.h>
#include <cstring>
#include "string.h"
#include <unordered_map>
#include <algorithm>
#include <cctype>

using namespace std;
using namespace BNM;
using namespace BNM::Operators;
using namespace IL2CPP;
using namespace BNM::UnityEngine;
using namespace BNM::Structures::Mono;
using namespace BNM::Structures::Unity;
namespace fs = std::filesystem;

Class scrPlanet{};
Image il2cpp;
void (*old_start)(UnityEngine::Object *);
void (*old_scrShowIfDebug_Update)(UnityEngine::Object *);
void (*old_scrEnableIfBeta_Awake)(UnityEngine::Object *);
void (*old_ADOStartup_Startup)(UnityEngine::Object *);
void (*old_scrController_Restart)(UnityEngine::Object *);
void (*old_SFB_StandaloneFileBrowser_OpenFilePanel)(UnityEngine::Object *);
void (*old_SFB_StandaloneFileBrowser_SaveFilePanelAsync)(UnityEngine::Object *);
void (*old_ResetScene)(UnityEngine::Object *);

UnityEngine::Object *floors;
bool isStarted = false;
UnityEngine::Object *scrController;
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, [[maybe_unused]] void *reserved) {
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    // Load BNM by finding the path to libil2cpp.so
    BNM::Loading::TryLoadByJNI(env);
    BNM::Loading::AddOnLoadedEvent(start);

   // __android_log_print(6,"TAG","JNI_OnLoaded");
    return JNI_VERSION_1_6;
}
/*
extern "C" {
JNIEXPORT jstring JNICALL Java_hitmargin_adofai_modifer_Native_onClick(JNIEnv *env, jclass) {
    return charToJstring(env,"onClick");
}

jstring charToJstring(JNIEnv *env, const char *pat) {
    return (*env).NewStringUTF(pat);
}
}
*/
extern "C"
JNIEXPORT void JNICALL
Java_hitmargin_adofai_modifer_Native_setResolution(JNIEnv *env, jclass clazz, jint x, jint y) {
    // TODO: implement setResolution()
    pixels[0] = x;
    pixels[1] = y;
}


void scrShowIfDebug(UnityEngine::Object *instance);

void scrShowIfDebug(UnityEngine::Object *instance) {
    /*
    UnityEngine::Object *txt = getFieldValue<UnityEngine::Object *>("","scrShowIfDebug","txt",instance);
    Structures::Mono::String *text = getFieldValue<Structures::Mono::String *>("UnityEngine.UI","Text","m_Text",txt);

    Field<Structures::Mono::String *> textVar = Class("","scrShowIfDebug").GetField("txt");
    std::string str("");
    str.append("curBPM:");
    str.append(std::to_string(curBPM));
    str.append("\n").append("realBPM").append(std::to_string(realBPM));
    str.append("\n").append("Multiplier::");
    str.append(std::to_string(multiplier));
    str.append("\n").append("frequency::");
    str.append(std::to_string(frequency));
    str.append("\n").append("checkpointsUsed::");
    str.append(std::to_string(checkpoints));
    str.append("\n").append("currentTile::");
    str.append(std::to_string(currentTile));
    str.append("\n").append("totalTile::");
    str.append(std::to_string(totalTile));
    str.append("\n").append("highestBPM::");
    str.append(std::to_string(highestBPM));
    str.append("\n").append("percentXAcc::");
    str.append(std::to_string(percentXAcc));
    str.append("\n").append("percentAcc::");
    str.append(std::to_string(percentAcc));
    str.append("\n").append("progress::");
    str.append(std::to_string(progress));
    str.append("\n").append("ms::");
    str.append(std::to_string(ms));
    

    textVar[text] = CreateMonoString(str);
    //__android_log_print(2,"TAG","text:%s",textVar[text].Get()->str().c_str());
    */
}

enum HitMargin {
    TooEarly,
    VeryEarly,
    EarlyPerfect,
    Perfect,
    LatePerfect,
    VeryLate,
    TooLate,
    Multipress,
    FailMiss,
    FailOverload,
	Auto
};
/*
enum Difficulty {
    Lenient,
    Normal,
    Strict
};
*/
/*
enum SystemLanguage
    {
        Afrikaans,
        Arabic,
        Basque,
        Belarusian,
        Bulgarian,
        Catalan,
        Chinese,
        Czech,
        Danish,
        Dutch,
        English,
        Estonian,
        Faroese,
        Finnish,
        French,
        German,
        Greek,
        Hebrew,
        Icelandic = 19,
        Indonesian,
        Italian,
        Japanese,
        Korean,
        Latvian,
        Lithuanian,
        Norwegian,
        Polish,
        Portuguese,
        Romanian,
        Russian,
        SerboCroatian,
        Slovak,
        Slovenian,
        Spanish,
        Swedish,
        Thai,
        Turkish,
        Ukrainian,
        Vietnamese,
        ChineseSimplified,
        ChineseTraditional,
        Unknown,
        Hungarian = 18
	};
*/
enum SystemLanguage {
    ChineseSimplified,
    German,
    Japanese,
    Korean,
    ChineseTraditional,
    Czech,
    Vietnamese,
    Russian,
    Romanian,
    Polish,
    French,
    Portuguese,
    Spanish,
    English
};

enum DifficultyUIMode
{
    DontShow,
     ShowLenientAndNormal,
     ShowNormalAndStrict,
     ShowAll
};
void (*old_scrController_PlayerControl_Update)(UnityEngine::Object *);
void PlayerUpdate(UnityEngine::Object *instance) {
    old_scrController_PlayerControl_Update(instance);
    /*
    UnityEngine::Object* controller = getFieldValue<UnityEngine::Object *>("","scrController","_instance",
                                                                         nullptr);
    scrController = controller;
    UnityEngine::Object* customLevel = getFieldValue<UnityEngine::Object *>("","CustomLevel","instance");
    /*UnityEngine::Object* customLevel = getFieldValue<UnityEngine::Object *>("","scnGame","instance");
    UnityEngine::Object* conductor = getFieldValue<UnityEngine::Object *>("","scrConductor","_instance");
    UnityEngine::Object* lm = getFieldValue<UnityEngine::Object *>("","scrLevelMaker","_instance");
    
        Field<float> currentSpeedTrial = Class("","GCS").GetField("currentSpeedTrial");
    float speedTrial = currentSpeedTrial.Get();
    /*
    Field<int> currentSeqID = Class("","scrController").GetField("currentSeqID"); 
    int currentSeqIDValue = currentSeqID[scrController].Get();
    currentTile = currentSeqIDValue;
    
    Field<UnityEngine::Object*> mistakesManagerField = Class("","scrController").GetField("mistakesManager");
    UnityEngine::Object* mistakesManager = mistakesManagerField[scrController].Get();
    Field<float> percentXAccField = Class("","scrMistakesManager").GetField("percentXAcc"); 
    float percentXAccValue = percentXAccField[mistakesManager].Get();
        if (std::isnan(percentXAccValue)) {
    percentXAccValue = 0;
    }
    percentXAcc = percentXAccValue;
    Field<float> percentAccField = Class("","scrMistakesManager").GetField("percentAcc"); 
    float percentAccValue = percentAccField[mistakesManager].Get();
    percentAcc = percentAccValue;
    Method<String*> sceneName = Class("","ADOBase").GetMethod("get_sceneName");
    Method<bool> get_isLevelSelect = Class("","ADOBase").GetMethod("get_isLevelSelect");
    
        //if (sceneName.Call()->str() == "scnEditor") {
            if (get_isLevelSelect.Call() == false) {
            Method<float> percentCompleteMethod = Class("","scrController").GetMethod("get_percentComplete"); 
    float percentCompleteValue = percentCompleteMethod[scrController].Call();
    progress = percentCompleteValue;
    }
    /*
    auto autoClass = Class("","scrFloor");
    Field<int> GetlastTogglePauseFrame = Class("","scrController").GetField("lastTogglePauseFrame"); 
    int lastTogglePauseFrameValue = GetlastTogglePauseFrame[scrController].Get();
    lastTogglePauseFrame = lastTogglePauseFrameValue;
    
    Field<UnityEngine::Object*> errorMeterField = Class("","scrController").GetField("errorMeter");
    UnityEngine::Object* errorMeter = errorMeterField[scrController].Get();
    Field<float> averageAngleField = Class("","scrHitErrorMeter").GetField("averageAngle"); 
    float averageAngleValue = averageAngleField[errorMeter].Get();
    ms = averageAngleValue;
    /*
    Field<int> deaths = Class("","scrController").GetField("deaths"); 
    int deathsValue = deaths.Get(); 
    frequency = deathsValue;
    Field<int> checkpointsUsed = Class("","scrController").GetField("checkpointsUsed"); 
    int checkpointsUsedValue = checkpointsUsed.Get();
    checkpoints = checkpointsUsedValue;
    
    Field<float> highestBPMField = Class("","scrLevelMaker").GetField("highestBPM"); 
    Method<float> songPitch = Class("UnityEngine","AudioSource").GetMethod("get_pitch");
    UnityEngine::Object* audioSource = getFieldValue<UnityEngine::Object *>("","scrConductor","song",conductor);
    float PitchAll = songPitch[audioSource].Call();
    float highestBPMValue = highestBPMField[lm].Get();
    highestBPM = highestBPMValue * PitchAll;
    //clickPerSecond = realBPM / 60;
    if (speedTrial != 1) {
    speedOfSpeedTrial = speedTrial;
    speed = speedOfSpeedTrial;
    } else {
        if (speedOfPitch != 1) {
            speed = speedOfPitch;
        } else {
            speed = 1;
        }
    }
    /*
    Field<int> lastHitMarginsSizeField = Class("","scrMistakesManager").GetField("lastHitMarginsSize");
    int lastHitMarginsSizeValue = lastHitMarginsSizeField.Get();
    lastHitMarginsSize = lastHitMarginsSizeValue;
    Method<float> getTotalHitsMethod = Class("","scrMistakesManager").GetMethod("GetTotalHits");
    float getTotalHitsValue = getTotalHitsMethod[mistakesManager].Call();
    getTotalHits = getTotalHitsValue;
    /*
    Method<int> getHitsMethod = Class("","scrMistakesManager").GetMethod("GetHits");
    int tooEarlyNumValue = getHitsMethod[mistakesManager].Call(0);
    tooEarlyNum = tooEarlyNumValue;
    int veryEarlyNumValue = getHitsMethod[mistakesManager].Call(1);
    veryEarlyNum = veryEarlyNumValue;
    int earlyPerfectNumValue = getHitsMethod[mistakesManager].Call(2);
    earlyPerfectNum = earlyPerfectNumValue;
    int perfectNumValue = getHitsMethod[mistakesManager].Call(3);
    perfectNum = perfectNumValue;
    int latePerfectNumValue = getHitsMethod[mistakesManager].Call(4);
    latePerfectNum = latePerfectNumValue;
    int veryLateNumValue = getHitsMethod[mistakesManager].Call(5);
    veryLateNum = veryLateNumValue;
    int tooLateNumValue = getHitsMethod[mistakesManager].Call(6);
    tooLateNum = tooLateNumValue;
    int multipressNumValue = getHitsMethod[mistakesManager].Call(7);
    multipressNum = multipressNumValue;
    int failMissNumValue = getHitsMethod[mistakesManager].Call(8);
    failMissNum = failMissNumValue;
    int failOverloadNumValue = getHitsMethod[mistakesManager].Call(9);
    failOverloadNum = failOverloadNumValue;
    */
    Method<bool> Dev = Class("UnityEngine","Application").GetMethod("get_isEditor");
    bool DevValue = Dev.Call();
    Developer = BoolToStr(DevValue);
    /*
    Field<Difficulty> hardestDifficulty = Class("","GCS").GetField("difficulty");
    Difficulty DifficultyValue = hardestDifficulty.Get();
    difficulty = DifficultyValue;
    DifficultyString = DifficultyToStr(DifficultyValue);
    Field<int> checkpointNum = Class("","GCS").GetField("_checkpointNum");
    int checkpointNumValue = checkpointNum.Get();
    CheckpointNum = checkpointNumValue;
    /*
    Method<bool> GetPerfectsOnlyMode = Class("","Persistence").GetMethod("GetPerfectsOnlyMode");
    bool PerfectsOnlyModeValue = GetPerfectsOnlyMode.Call();
    PerfectsOnlyMode = BoolToStr(PerfectsOnlyModeValue);
    */
    
    /*
    Method<float> _marginScale = Class("","scrController").GetMethod("get__marginScale");
    float MarginScaleValue = _marginScale[controller].Call();
    margin = MarginScaleValue *100;
    //以下为debug
    /*
    UnityEngine::Object* GetEvents = callMethod<UnityEngine::Object *>("","CustomLevel","get_events",customLevel);
    //UnityEngine::Object* levelData = getFieldValue<UnityEngine::Object *>("","CustomLevel","LevelData",customLevel);
    UnityEngine::Object* ScaleMargin = getFieldValue<UnityEngine::Object *>("ADOFAI","ListItem","sourceLevelEvent");
   // Il2CppObject *levelEvents = Class("ADOFAI","LevelEvent").CreateNewObjectParameters();
   Method<int> marginMet = Class("ADOFAI","LevelEvent").GetMethod("GetInt");
    margin = marginMet[GetEvents].Call(CreateMonoString("scale"));
    */
    //DifficultyString = DifficultyToStr(Difficulty);
    /*Class ADOBase = Class("","ADOBase");
    Method<bool> isLevelEditor = ADOBase.GetMethod("get_isLevelEditor");
    if (isLevelEditor.Call() == false) {
    Class GCNS = Class("","GCNS");
    Field<Structures::Mono::String* > sceneLevelSelect = GCNS.GetField("sceneLevelSelect");
    sceneLevelSelect.Set(CreateMonoString("scnEditor"));
    Method<void> goToLevel = Class("","ADOBase").GetMethod("GoToLevelSelect");
    goToLevel.Call();
    }*/
    //LoadLevelEditor();
    //__android_log_print(2,"TAG","curBPM:%f,realBPM:%f,Multiplier:%f,currentTile:%f,percentXAcc:%f,percentAcc:%f,progress:%f,ms:%f,clickPerSecond:%f",curBPM,realBPM,multiplier,currentTile,percentXAcc,percentAcc,progress,ms,clickPerSecond);
    UnityEngine::Object* lm = getFieldValue<UnityEngine::Object *>("","scrLevelMaker","_instance");
    UnityEngine::Object* conductor = getFieldValue<UnityEngine::Object *>("","scrConductor","_instance");
    UnityEngine::Object* audioSource = getFieldValue<UnityEngine::Object *>("","scrConductor","song",conductor);
    Method<float> musicTimeMet = Class("UnityEngine","AudioSource").GetMethod("get_time");
    float musicTimeValue = musicTimeMet[audioSource].Call();
    musicTime = musicTimeValue;
    UnityEngine::Object* audioClip = callMethod<UnityEngine::Object *>("UnityEngine","AudioSource","get_clip",audioSource);
    Method<float> musicTotalTimeMet = Class("UnityEngine","AudioClip").GetMethod("get_length");
    float musicTotalTimeValue = musicTotalTimeMet[audioClip].Call();
    totalTime = musicTotalTimeValue;

    Field<float> addoffsetFie = Class("","scrConductor").GetField("addoffset");
    float addoffsetValue = addoffsetFie[conductor].Get();
    Method<double> songposition_minusiMet = Class("","scrConductor").GetMethod("get_songposition_minusi");
    float songposition_minusiValue = songposition_minusiMet[conductor].Call();

    mapTime_f = musicTotalTimeValue + songposition_minusiValue;
    /*
    UnityEngine::Object* listFloorPtr = getFieldValue<UnityEngine::Object*>("","scrLevelMaker","listFloors",lm);
    UnityEngine::Object lastFloor = Last(listFloorPtr);
    */
    Class scrFloor = Class("","scrFloor");
    Field<double> entryTimeVar = scrFloor.GetField("entryTime");
    double entryTimeVarAll = entryTimeVar[floors].Get();
    double mapTimeTotalVal = entryTimeVarAll;
    mapTime = mapTimeTotalVal;
}


void adofaiStart(UnityEngine::Object *instance) {
    old_ADOStartup_Startup(instance);
    /*
    UnityEngine::Object* controller = getFieldValue<UnityEngine::Object *>("","scrController","_instance",
                                                                         nullptr);
                                      
    //正常冰与火之舞需要删除以下修改
    /*Field<String*> sceneToLoadField = Class("", "GCS").GetField("sceneToLoad");
    sceneToLoadField.Set(CreateMonoString("scnEditor"));
    Class GCNS = Class("","GCNS");
    Field<String* > sceneLevelSelect = GCNS.GetField("sceneLevelSelect");
    sceneLevelSelect.Set(CreateMonoString("scnEditor"));
    /*Method <bool> useOldAutoValue = Class("", "RDC").GetMethod("set_useOldAuto");
    useOldAutoValue.Call(true);
    Field<int> planetsUsedField = Class("", "scrController").GetField("planetsUsed");
    planetsUsedField[controller].Set(4);*/
    /*Field<int> checkpointNumField = Class("", "GCS").GetField("_checkpointNum");
    checkpointNumField.Set(114);*/
    //Gotoleveleditor();
    /*Field<bool> useNoFail = Class("", "GCS").GetField("useNoFail");
    useNoFail.Set(true);*/
    //Gotoleveleditor();
    //LoadScene();
    /*Class GCNS = Class("","GCNS");
    Field<String* > sceneLevelSelect = GCNS.GetField("sceneLevelSelect");
    sceneLevelSelect.Set(CreateMonoString("scnMobileMenu"));
    */
    Method<bool> Dev = Class("UnityEngine","Application").GetMethod("get_isEditor");
        bool DevValue = Dev.Call();
        //if (DevValue) {
            Field<bool> hasTaroDLC = Class("","ADOBase").GetField("hasTaroDLC");
            Field<bool> ownsTaroDLC = Class("","ADOBase").GetField("ownsTaroDLC");
            hasTaroDLC.Set(true);
            ownsTaroDLC.Set(true);
        //}
}

void (*old_MoveToNextFloor)(UnityEngine::Object *,UnityEngine::Object *,UnityEngine::Object *,UnityEngine::Object *);
void MoveToNextFloor(UnityEngine::Object *arg0, UnityEngine::Object *arg1,UnityEngine::Object *arg2,UnityEngine::Object *arg3) {
    old_MoveToNextFloor(arg0,arg1,arg2,arg3);
    floors = arg1;
    Class scrFloor = Class("","scrFloor");
    Field<double> entryTimeVar = scrFloor.GetField("entryTime");
    Field<UnityEngine::Object *> nextFloorVar = scrFloor.GetField("nextfloor");
    UnityEngine::Object* nextFloor = nextFloorVar[arg1].Get();
    Field<double> marginScale = scrFloor.GetField("marginScale");
    Field<UnityEngine::Object *> prevFloorVar = scrFloor.GetField("prevFloor");
    UnityEngine::Object* prevFloor = prevFloorVar[arg1].Get();
    //marginScale[arg0].Set(123456.25);
    /*
    double entryTime = entryTimeVar[arg1].Get();
    double nextEntryTime = entryTimeVar[nextFloor].Get();
    bool Twirl = isTwirl();
     */
    UnityEngine::Object* conductor = getFieldValue<UnityEngine::Object *>("","scrConductor","_instance");
    UnityEngine::Object* lm = getFieldValue<UnityEngine::Object *>("","scrLevelMaker","_instance");
    UnityEngine::Object* customLevel = getFieldValue<UnityEngine::Object *>("","CustomLevel","instance");
    UnityEngine::Object* controller = getFieldValue<UnityEngine::Object *>("","scrController","_instance");
    Field<float> levelBPM = Class("","scrConductor").GetField("bpm");
    Field<double> speed = Class("", "scrController").GetField("speed");
    Field<float> currentSpeedTrial = Class("","GCS").GetField("currentSpeedTrial");
    float speedTrial = currentSpeedTrial.Get();
    Method<float> songPitch = Class("UnityEngine","AudioSource").GetMethod("get_pitch");
    UnityEngine::Object* audioSource = getFieldValue<UnityEngine::Object *>("","scrConductor","song",conductor);
    float PitchAll = songPitch[audioSource].Call();
    //curBPM = levelBPM[conductor].Get() * speed[scrController].Get() * speedOfPitch * speedTrial;
    curBPM = levelBPM[conductor].Get() * PitchAll * speed[controller].Get();
    //lastBPM = realBPM / speedOfPitch * speedTrial;
    lastBPM = realBPM / PitchAll;
    //realBPM = getRealBPM(arg1,nextFloor,bpm) * speedOfPitch * speedTrial;
    realBPM = getRealBPM(arg1,nextFloor,bpm) * PitchAll;
    static double prevAvgBPM = 0.0;
    avgBPM = fabs(getRealBPM(arg1, prevFloor, bpm) * PitchAll);
    if (isinf(avgBPM)) {
        avgBPM = prevAvgBPM;
    } else {
        prevAvgBPM = avgBPM;
    }
    multiplier = speed[controller].Get();
    clickPerSecond = realBPM / 60;
    UnityEngine::Object* currFloor = callMethod<UnityEngine::Object *>("","scrController","get_currFloor", controller);
    Field<double> MarginScale = Class("","scrFloor").GetField("marginScale");
    double MarginScaleValue = MarginScale[currFloor].Get();
    margin = MarginScaleValue *100;
    /*
        Field<float> currentSpeedTrial = Class("","GCS").GetField("currentSpeedTrial");
    float speedTrial = currentSpeedTrial.Get();
    /*
    Field<int> currentSeqID = Class("","scrController").GetField("currentSeqID"); 
    int currentSeqIDValue = currentSeqID[scrController].Get();
    currentTile = currentSeqIDValue;
    */
    Field<UnityEngine::Object*> mistakesManagerField = Class("","scrController").GetField("mistakesManager");
    UnityEngine::Object* mistakesManager = mistakesManagerField[controller].Get();
    Field<float> percentXAccField = Class("","scrMistakesManager").GetField("percentXAcc"); 
    float percentXAccValue = percentXAccField[mistakesManager].Get();
        if (std::isnan(percentXAccValue)) {
    percentXAccValue = 0;
    }
    percentXAcc = percentXAccValue;
    Field<float> percentAccField = Class("","scrMistakesManager").GetField("percentAcc"); 
    float percentAccValue = percentAccField[mistakesManager].Get();
    percentAcc = percentAccValue;
    Method<String*> sceneName = Class("","ADOBase").GetMethod("get_sceneName");
    Method<bool> get_isLevelSelect = Class("","ADOBase").GetMethod("get_isLevelSelect");
    
        //if (sceneName.Call()->str() == "scnEditor") {
            if (get_isLevelSelect.Call() == false) {
            Method<float> percentCompleteMethod = Class("","scrController").GetMethod("get_percentComplete"); 
    float percentCompleteValue = percentCompleteMethod[controller].Call();
    progress = percentCompleteValue;
    }
    /*
    auto autoClass = Class("","scrFloor");
    Field<int> GetlastTogglePauseFrame = Class("","scrController").GetField("lastTogglePauseFrame"); 
    int lastTogglePauseFrameValue = GetlastTogglePauseFrame[scrController].Get();
    lastTogglePauseFrame = lastTogglePauseFrameValue;
    */
    /*
    Field<UnityEngine::Object*> errorMeterField = Class("","scrController").GetField("errorMeter");
    UnityEngine::Object* errorMeter = errorMeterField[controller].Get();
    Field<float> averageAngleField = Class("","scrHitErrorMeter").GetField("averageAngle"); 
    float averageAngleValue = averageAngleField[errorMeter].Get();
    ms = averageAngleValue;
    /*
    Field<int> deaths = Class("","scrController").GetField("deaths"); 
    int deathsValue = deaths.Get(); 
    frequency = deathsValue;
    Field<int> checkpointsUsed = Class("","scrController").GetField("checkpointsUsed"); 
    int checkpointsUsedValue = checkpointsUsed.Get();
    checkpoints = checkpointsUsedValue;
    */
    /*
    Field<float> highestBPMField = Class("","scrLevelMaker").GetField("highestBPM"); 
    
    float highestBPMValue = highestBPMField[lm].Get();
    highestBPM = highestBPMValue * PitchAll;
    //clickPerSecond = realBPM / 60;
    /*
    if (speedTrial != 1) {
    speedOfSpeedTrial = speedTrial;
    speed = speedOfSpeedTrial;
    } else {
        if (speedOfPitch != 1) {
            speed = speedOfPitch;
        } else {
            speed = 1;
        }
    }
*/    
    Method<int> getHitsMethod = Class("","scrMistakesManager").GetMethod("GetHits");
    int tooEarlyNumValue = getHitsMethod[mistakesManager].Call(0);
    tooEarlyNum = tooEarlyNumValue;
    int veryEarlyNumValue = getHitsMethod[mistakesManager].Call(1);
    veryEarlyNum = veryEarlyNumValue;
    int earlyPerfectNumValue = getHitsMethod[mistakesManager].Call(2);
    earlyPerfectNum = earlyPerfectNumValue;
    int perfectNumValue = getHitsMethod[mistakesManager].Call(3);
    perfectNum = perfectNumValue;
    int latePerfectNumValue = getHitsMethod[mistakesManager].Call(4);
    latePerfectNum = latePerfectNumValue;
    int veryLateNumValue = getHitsMethod[mistakesManager].Call(5);
    veryLateNum = veryLateNumValue;
    int tooLateNumValue = getHitsMethod[mistakesManager].Call(6);
    tooLateNum = tooLateNumValue;
    int multipressNumValue = getHitsMethod[mistakesManager].Call(7);
    multipressNum = multipressNumValue;
    int failMissNumValue = getHitsMethod[mistakesManager].Call(8);
    failMissNum = failMissNumValue;
    int failOverloadNumValue = getHitsMethod[mistakesManager].Call(9);
    failOverloadNum = failOverloadNumValue;
}

void startPlay(UnityEngine::Object *instance) {
    old_start(instance);
    //__android_log_print(3,"TAG","Play()");
    
    Field<float> currentSpeedTrial = Class("","GCS").GetField("currentSpeedTrial");
    float speedTrial = currentSpeedTrial.Get();
    UnityEngine::Object* floor = getFieldValue<UnityEngine::Object *>("","scrFloor","_instance");
    UnityEngine::Object* controller = getFieldValue<UnityEngine::Object *>("","scrController","_instance");
    UnityEngine::Object* customLevel = getFieldValue<UnityEngine::Object *>("","CustomLevel","instance");
    UnityEngine::Object* conductor = getFieldValue<UnityEngine::Object *>("","scrConductor","_instance");
    UnityEngine::Object* lm = getFieldValue<UnityEngine::Object *>("","scrLevelMaker","_instance");
    Method<float> songPitch = Class("UnityEngine","AudioSource").GetMethod("get_pitch");
    UnityEngine::Object* audioSource = getFieldValue<UnityEngine::Object *>("","scrConductor","song",conductor);
    float PitchAll = songPitch[audioSource].Call();
    Field<float> currBPM = Class("","scrConductor").GetField("bpm");
    curBPM = currBPM[conductor].Get();
    bpm = curBPM * PitchAll;
    Field<int> deaths = Class("","scrController").GetField("deaths"); 
    int deathsValue = deaths.Get() +1; 
    //__android_log_print(2, "TAG", "Deaths: %d", deathsValue);
    frequency = deathsValue;
    Field<int> checkpointsUsed = Class("","scrController").GetField("checkpointsUsed"); 
    int checkpointsUsedValue = checkpointsUsed.Get();
    checkpoints = checkpointsUsedValue;
    Field<float> highestBPMField = Class("","scrLevelMaker").GetField("highestBPM"); 
    float highestBPMValue = highestBPMField[lm].Get();
    //highestBPM = highestBPMValue * speedOfPitch * speedTrial;
    UnityEngine::Object* levelData = getFieldValue<UnityEngine::Object *>("","CustomLevel","levelData",customLevel);
    UnityEngine::Object* levelEvent = getFieldValue<UnityEngine::Object *>("ADOFAI","LevelData","songSettings",levelData);
    Method<int> pitchMet = Class("ADOFAI","LevelEvent").GetMethod("GetInt");
    pitch = pitchMet[levelEvent].Call(CreateMonoString("pitch"));
    //Structures::Mono::List *listFloor = getFieldValue<Structures::Mono::List *>("","scrLevelMaker","listFloors",lm);
    //int listFloorValue = listFloor;
    
    speedOfPitch = pitch / 100.0;
    speed = speedOfPitch;
    progress = 0;
    percentXAcc = 0;
    percentAcc = 0;
    currentTile = 0;
    realBPM = 0;
    multiplier = 0;
    ms = 0;
    clickPerSecond = 0;
    lastHitMarginsSize = 0;
    getTotalHits = 0;
    tooEarlyNum = 0;
    veryEarlyNum = 0;
    earlyPerfectNum = 0;
    perfectNum = 0;
    latePerfectNum = 0;
    veryLateNum = 0;
    tooLateNum = 0;
    multipressNum = 0;
    failMissNum = 0;
    failOverloadNum = 0;
    score = 0;
    PerfectCombo = 0;

    Field<UnityEngine::Object*> mistakesManagerField = Class("","scrController").GetField("mistakesManager");
    UnityEngine::Object* mistakesManager = mistakesManagerField[controller].Get();
    Field<float> percentXAccField = Class("","scrMistakesManager").GetField("percentXAcc"); 
    float percentXAccValue = percentXAccField[mistakesManager].Get();
        if (std::isnan(percentXAccValue)) {
    percentXAccValue = 0;
    }
    percentXAcc = percentXAccValue;
    Field<float> percentAccField = Class("","scrMistakesManager").GetField("percentAcc"); 
    float percentAccValue = percentAccField[mistakesManager].Get();
    percentAcc = percentAccValue;
    /*
    Field<int> GetlastTogglePauseFrame = Class("","scrController").GetField("lastTogglePauseFrame"); 
    int lastTogglePauseFrameValue = GetlastTogglePauseFrame[scrController].Get();
    lastTogglePauseFrame = lastTogglePauseFrameValue;
    /*Field<int> listFloorsCountField = Class("", "scrLevelMaker").GetField("listFloors.Count");
    int listFloorsCount = listFloorsCountField.Get();
    totalTile = listFloorsCount - 1;*/
    /*Field<int> checkpointNumField = Class("", "GCS").GetField("_checkpointNum");
    checkpointNumField.Set(10);*/
    /*
    Method<float> _marginScale = Class("","scrController").GetMethod("get__marginScale");
    float MarginScaleValue = _marginScale[controller].Call();
    margin = MarginScaleValue *100;
    */
    
    highestBPM = highestBPMValue * PitchAll;
    /*
    UnityEngine::Object* currFloor = callMethod<UnityEngine::Object *>("","scrController","get_currFloor", controller);
    Field<double> MarginScale = Class("","scrFloor").GetField("marginScale");
    double MarginScaleValue = MarginScale[currFloor].Get();
    margin = MarginScaleValue *100;
    /*
        Method<bool> Dev = Class("UnityEngine","Application").GetMethod("get_isEditor");
        bool DevValue = Dev.Call();
        Developer = BoolToStr(DevValue);
        /*
        Field<Difficulty> hardestDifficulty = Class("","GCS").GetField("difficulty");
        Difficulty DifficultyValue = hardestDifficulty.Get();
        difficulty = DifficultyValue;
        DifficultyString = DifficultyToStr(DifficultyValue);
        Field<int> checkpointNum = Class("","GCS").GetField("_checkpointNum");
        int checkpointNumValue = checkpointNum.Get();
        CheckpointNum = checkpointNumValue;
        
        Method<bool> GetPerfectsOnlyMode = Class("","Persistence").GetMethod("GetPerfectsOnlyMode");
    bool PerfectsOnlyModeValue = GetPerfectsOnlyMode.Call();
    PerfectsOnlyMode = BoolToStr(PerfectsOnlyModeValue);
    /*auto ButtonClass = Class("UnityEngine.UI", "Button");
    auto gameObject = Class("UnityEngine", "gameObject");
    auto SetActive = gameObject.GetMethod("SetActive");
    UnityEngine::Object* UIController = getFieldValue<UnityEngine::Object *>("","scrUIController","_instance");
    Field<UnityEngine::Object*> pauseButton = Class("","scrUIController").GetField("pauseButton");
    pauseButton[UIController].SetActive(false);*/
    //__android_log_print(3,"TAG","pitch:%d,speed:%f,checkpoints:%f,highestBPM:%f",pitch,speedOfPitch,checkpoints,highestBPM);
}






void debugValue() {
Method<void> getDebugMethod = Class("", "RDC").GetMethod("set_debug");
getDebugMethod.Call(true);
}

void Gotoleveleditor() {
    
    Class GCNS = Class("","GCNS");
    Field<Structures::Mono::String* > sceneLevelSelect = GCNS.GetField("sceneLevelSelect");
    sceneLevelSelect.Set(CreateMonoString("scnEditor"));
    
}
void LoadLevelEditor() {
    /*
    Class ADOBase = Class("","ADOBase");
    Method<bool> isLevelEditor = ADOBase.GetMethod("get_isLevelEditor");
    Class ADOStartup = Class("","ADOStartup");
    Field<bool> startup = ADOStartup.GetField("startup");
    if (isLevelEditor.Call() == false && startup.Get() == true) {
    Method<void> loadScene = Class("","ADOBase").GetMethod("LoadScene");
    loadScene.Call(CreateMonoString("scnEditor"));
    }
    */
}
void GoToNeoCosmos() {
    /*Class GCNS = Class("","GCNS");
    Field<Structures::Mono::String* > sceneLevelSelect = GCNS.GetField("sceneLevelSelect");
    sceneLevelSelect.Set(CreateMonoString("scnTaroMenu0"));
    */
}
void LoadScene() {
        Field<String*> sceneToLoadField = Class("", "GCS").GetField("sceneToLoad");
    sceneToLoadField.Set(CreateMonoString("scnEditor"));
}
void newRestart(UnityEngine::Object *instance) {
    old_scrController_Restart(instance);
    /*UnityEngine::Object* controller = getFieldValue<UnityEngine::Object *>("","scrController","_instance",
                                                                         nullptr);
    Method<void> loadCustomLevelMethod = Class("", "scrController").GetMethod("LoadCustomLevel");
    Method<string> levelPath = Class("", "Persistence").GetMethod("GetLastOpenedLevel");
    loadCustomLevelMethod[controller].Call(CreateMonoString("/sdcard/levels/level/main.adofai"));
    //loadCustomLevelMethod[controller].Call(CreateMonoString(levelPath.Call()));
    */
    /*Class GCNS = Class("","GCNS");
    Field<Structures::Mono::String* > sceneLevelSelect = GCNS.GetField("sceneLevelSelect");
    sceneLevelSelect.Set(CreateMonoString("scnEditor"));
    Method<void> goToLevel = Class("","ADOBase").GetMethod("GoToLevelSelect");
    goToLevel.Call();
    */
    //Method<void> loadScene = Class("","ADOBase").GetMethod("LoadScene");
    //loadScene.Call(CreateMonoString("scnEditor"));
    
}
void (*old_scrController_QuitToMainMenu)(UnityEngine::Object *);
void load(UnityEngine::Object *instance) {
    old_scrController_QuitToMainMenu(instance);
    /*UnityEngine::Object* controller = getFieldValue<UnityEngine::Object *>("","scrController","_instance",
                                                                         nullptr);
    Method<void> loadCustomWorldMethod = Class("", "scrController").GetMethod("LoadCustomWorld");
    loadCustomWorldMethod[controller].Call(CreateMonoString("/sdcard/levels/level/main.adofai"));
    /*Field<Structures::Mono::String *> sceneToLoadField = Class("", "GCS").GetField("sceneToLoad");
    sceneToLoadField.Set(CreateMonoString("scnEditor"));
    */
    //GoToNeoCosmos();
    //正常冰与火需要删除以下修改
   /* Field<String*> sceneToLoadField = Class("", "GCS").GetField("sceneToLoad");
    sceneToLoadField.Set(CreateMonoString("scnEditor"));
    
    //LoadScene();*/
}
/*
string levelPath() {
    Method<String*> levelPathMethod = Class("", "Persistence").GetMethod("GetLastOpenedLevel");
    auto Path = levelPathMethod.Call()->str();
    return Path;
}
*/
// 忽略大小写的字符串比较函数
bool acasecmp(const std::string& a, const std::string& b) {
    auto strCmp = [](char a, char b) {
        return std::tolower(a) == std::tolower(b);
    };
    return std::equal(a.begin(), a.end(), b.begin(), b.end(), strCmp);
}

String* OpenedLevelMet() {
    std::vector<std::string> files;
    try {
        // 获取目录中的所有.adofai文件
        for (const auto& entry : fs::directory_iterator("/sdcard/levels/level/")) {
            if (entry.is_regular_file() && entry.path().extension() == ".adofai") {
                files.push_back(entry.path().string());
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << '\n';
        return CreateMonoString("");
    }

std::sort(files.begin(), files.end(), [](const std::string& a, const std::string& b) {
        return acasecmp(a, b);
    });

    // 查找第一个不是"backup.adofai"的文件
    for (const auto& file : files) {
        if (fs::path(file).filename().string() != "backup.adofai") {
            return CreateMonoString(std::string(file));
        }
    }

    return CreateMonoString("");
}



Array<String *> *openFilePanel(String title, String directory, String extensions, bool multiselect) {
    syncFrameCount();
    auto strs = Array<String *>::Create({CreateMonoString(OpenedLevelMet()->str())});
    Method<String*> levelPathMethod = Class("", "Persistence").GetMethod("GetLastOpenedLevel");
    auto Path = OpenedLevelMet()->str();
    auto level = Array<String *>::Create({CreateMonoString("/sdcard/levels/level/main.adofa")});
    /*
    if (Path.empty()) {
        return level;
    } else {
        */
            return strs;
//    }
}

void saveFilePanelAsync(String title, String directory, String defaultName, String extension, Action<String *> cb) {
    Method<String*> levelPathMethod = Class("", "Persistence").GetMethod("GetLastOpenedLevel");
    auto Path = levelPathMethod.Call()->str();
    //if (Path.empty()) {
    cb.Invoke(CreateMonoString("/sdcard/levels/level/main.adofai"));
    /*
    } else {
        cb.Invoke(CreateMonoString(Path));
    }
    */
}

void syncFrameCount() {
    Method<int> getFrameCount = Class("UnityEngine","Time").GetMethod("get_frameCount");
    Field<int> lastFrameCount = Class("SFB","StandaloneFileBrowser").GetField("lastFrameCount");
    lastFrameCount.Set(getFrameCount.Call());
}

void ResetScene(UnityEngine::Object *instance) {
    old_ResetScene(instance);
    //isStarted = false;
    //__android_log_print(ANDROID_LOG_WARN,"TAG","ResetScene()");
}
double getRealBPM(UnityEngine::Object *floor, UnityEngine::Object *nextFloor, float bpm) {
    if (floor == nullptr) return bpm;
    if (nextFloor == nullptr) {
        return lastBPM;
    }
    Class scrFloor = Class("","scrFloor");
    Field<double> entryTimeVar = scrFloor.GetField("entryTime");
    double entryTime = entryTimeVar[floor].Get();
    double nextEntryTime = entryTimeVar[nextFloor].Get();
    return 60/(nextEntryTime - entryTime);
}

    
bool isTwirl() {
    Class scrController = Class("","scrController");
    Field<UnityEngine::Object *> instance = scrController.GetField("_instance");
    Field<bool> isCW = scrController.GetField("isCW");
    return isCW[instance.Get()].Get();
}
// 使用 const 修饰符防止意外修改
struct Translation {
    const char* autoplay;
    const char* autoTile;
};

// 优化点1: 使用 unordered_map 并声明为 const 提升查找性能
const std::unordered_map<std::string, SystemLanguage> languageMap = {
    {"ChineseSimplified", SystemLanguage::ChineseSimplified},
    {"German", SystemLanguage::German},
    {"Japanese", SystemLanguage::Japanese},
    {"Korean", SystemLanguage::Korean},
    {"ChineseTraditional", SystemLanguage::ChineseTraditional},
    {"Czech", SystemLanguage::Czech},
    {"Vietnamese", SystemLanguage::Vietnamese},
    {"Russian", SystemLanguage::Russian},
    {"Romanian", SystemLanguage::Romanian},
    {"Polish", SystemLanguage::Polish},
    {"French", SystemLanguage::French},
    {"Portuguese", SystemLanguage::Portuguese},
    {"Spanish", SystemLanguage::Spanish},
    {"English", SystemLanguage::English},
};

// 优化点2: 改用 unordered_map 提升查找效率
// 注意：需确保 SystemLanguage 已实现哈希函数
std::unordered_map<SystemLanguage, Translation> translations = {
    {SystemLanguage::ChineseSimplified, {"\n                  自动播放", "\n                  自动方块"}},
    {SystemLanguage::German, {"\n                  Automatische Wiedergabe", "\n                  Automatischer Block"}},
    {SystemLanguage::Japanese, {"\n                                      自動再生", "\n                                      自動タイル"}},
    {SystemLanguage::Korean, {"\n                  자동 플레이", "\n                  자동 플레이 타일"}},
    {SystemLanguage::ChineseTraditional, {"\n                  自動播放", "\n                  自動格子"}},
    {SystemLanguage::Czech, {"\n                  Automatické-Hraní", "\n                  Automatické Dlaždice"}},
    {SystemLanguage::Vietnamese, {"\n                  Tự chơi", "\n                  Gạch tự chơi"}},
    {SystemLanguage::Russian, {"\n                  Автоигра", "\n                  Авто тайл"}},
    {SystemLanguage::Romanian, {"\n                  Redare automată", "\n                  Placă auto"}},
    {SystemLanguage::Polish, {"\n                  Automatyczne odtwarzanie", "\n                  Automatyczne klocki"}},
    {SystemLanguage::French, {"\n                  Jeu-automatique", "\n                  Tuile automatique"}},
    {SystemLanguage::Portuguese, {"\n                  Automático", "\n                  Piso Automático"}},
    {SystemLanguage::Spanish, {"\n                  Automático", "\n                  Piso Automático"}},
    {SystemLanguage::English, {"\n                  Autoplay", "\n                  Auto tile"}},
};

// 优化点3: 使用 const 引用避免拷贝
SystemLanguage StringToSystemLanguage(const std::string& languageStr) {
    const auto it = languageMap.find(languageStr);
    return it != languageMap.end() ? it->second : SystemLanguage::English;
}

String* (*old_Persistence_GetLanguage)();
String* Persistence_GetLanguageMet() {
    return old_Persistence_GetLanguage();
}

// 优化点4: 合并多次字符串操作
SystemLanguage Persistence_GetLanguageMet_language() {
    if (String* languageStr = Persistence_GetLanguageMet()) {
        return StringToSystemLanguage(languageStr->str());
    }
    return SystemLanguage::English;
}

String* (*old_RDString_Get)(String*, Dictionary<String*, Il2CppObject*>*);
String* RDString_Get(String* key, Dictionary<String*, Il2CppObject*>* parameters) {
    // 优化点5: 缓存 key->str() 结果
    const std::string keyStr = key->str();
    
    // 优化点6: 提前判断高频 key 提升分支预测
    if (keyStr == "status.autoplay" || keyStr == "status.autoTile") {
        const SystemLanguage language = Persistence_GetLanguageMet_language();
        if (const auto it = translations.find(language); it != translations.end()) {
            return CreateMonoString(
                keyStr == "status.autoplay" ? 
                it->second.autoplay : 
                it->second.autoTile
            );
        }
    }

    // 优化点7: 使用短路表达式简化代码
    return old_RDString_Get ? old_RDString_Get(key, parameters) : key;
}


void (*old_OnGUI)(UnityEngine::Object *);
void OnGUI(UnityEngine::Object *instance) {
    Method<bool> Dev = Class("UnityEngine","Application").GetMethod("get_isEditor");
    bool devValue = Dev.Call();
    UnityEngine::Object* Controller = getFieldValue<UnityEngine::Object *>("","scrController","_instance");
    UnityEngine::Object* Conductor = getFieldValue<UnityEngine::Object *>("","scrConductor","_instance");
    Method<bool> paused = Class("","scrController").GetMethod("get_paused");
    Field<bool> _paused = Class("","scrController").GetField("_paused");
    Field<bool> isGameWorld = Class("","scrConductor").GetField("isGameWorld");
    
    isStarted = !_paused[Controller].Get() && isGameWorld[Conductor].Get()/* && Dev.Call()*/;
    string NotPlaying("<b>Not Playing\nMod By HitMargin (Mod Version : 1.3)</b>");
    string none(NotPlaying);
    string NotPlayingWithDev("<b>Not Playing\nMod By HitMargin (Mod Version : 1.3,<color=Red>Developer!!</color>)</b>");
    string dev(NotPlayingWithDev);

 
    if (isStarted) {
        
        float totalLength = totalTime;
        std::string totalLengthFormatted = secondsToMMSS(totalLength);

        float currentTime = musicTime;
        std::string currentTimeFormatted = secondsToMMSS(currentTime);
        std::string mapTimeFormatted = secondsToMMSS(mapTime);
        //Il2CppObject* customFont = LoadResourceFont("/sdcard/Font/Maplestory OTF Bold");
        char text[256 * 16];
    sprintf(text,//"<b>"
                 "Tile BPM | %.2f\n"
                 "Highest T BPM | %.2f\n"
                 "Cur BPM | %.2f\n"
                 "Avg BPM | %.2f\n"
                 "KPS | %.2f\n"
                 "Speed | %.2f\n\n"
                 "Music Time | %s ~ %s\n"
                 "Map Time | %s\n"
                 "Attempt | %d\n"
                 "Check Point | %d\n\n"
                 "Progress | %.2f%%\n"
                 "X-ACC | %.2f%%\n"
                 "ACC | %.2f%%\n\n"
                 "Perfect Combo | %d\n"
                 "Timing | %.2f \n"
                 "Timing Scale | %d%%\n"
                 " \t\t\t\t\t \n"
                 "                 <size=42>"
                 "<color=#E69AF6>%d</color> "
                 "<color=#FF0000>%d</color> "
                 "<color=#FF3333>%d</color> "
                 "<color=#FFFF00>%d</color> "
                 "<color=#00FF00>%d</color> "
                 "<color=#FFFF00>%d</color> "
                 "<color=#FF3333>%d</color> "
                 "<color=#FF0000>%d</color> "
                 "<color=#00FFFF>%d</color> "
                 "<color=#E69AF6>%d</color>"
                 "</size>"
                 //"</b>"
                 ,
            
            curBPM,
            highestBPM,
            realBPM,
            avgBPM,
            clickPerSecond,
            speed,
            currentTimeFormatted.c_str(),
            totalLengthFormatted.c_str(),
            mapTimeFormatted.c_str(),
            frequency, checkpoints,
            progress * 100,
            percentXAcc * 100,
            percentAcc * 100,
            PerfectCombo,

            ms, margin, failOverloadNum, tooEarlyNum, veryEarlyNum, earlyPerfectNum, perfectNum,
            latePerfectNum, veryLateNum, tooLateNum, multipressNum, failMissNum);
            // 以下为自定义颜色
    
        
/*
    const Color white = Color(1.0f, 1.0f, 1.0f);    // 白色
    const Color golden = Color(255.0f / 255.0f, 215.0f / 255.0f, 0.0f / 255.0f); // 金色
    const Color purple = Color(1.0f, 0.0f, 1.0f);   // 紫色

    // BPM 渐变（从白色到金色）
    float minBPM = 300.0f;
    float maxBPM = 2000.0f;
    float targetBPM = curBPM;
    float ratioBPM = (targetBPM - minBPM) / (maxBPM - minBPM);
    ratioBPM = std::max(0.0f, std::min(1.0f, ratioBPM));
    Color bpmColor = lerpColor(white, golden, ratioBPM);

    // Progress 渐变（从白色到金色）
    float ratioProgress = progress * 100 / 100.0f; // 应用实际的 progress 值
    Color progressColor = lerpColor(white, golden, ratioProgress);

    // X-ACC 和 ACC 渐变（低于1时从金色到紫色）
    Color xAccColor = lerpColor(golden, purple, 1.0f - percentXAcc);
    Color accColor = lerpColor(golden, purple, 1.0f - percentAcc);

    // Combo 渐变（从白色到金色）
    int mixCombo = 10;
    int maxCombo = 100;
    int targetCombo = PerfectCombo;

    float ratioCombo = 0.0f;
    if (maxCombo > mixCombo) {
        ratioCombo = static_cast<float>(targetCombo - mixCombo) / (maxCombo - mixCombo);
    }
    ratioCombo = std::max(0.0f, std::min(1.0f, ratioCombo));

    Color comboColor = lerpColor(white, golden, ratioCombo);

    float timeProgress = currentTime / totalLength;

    Color timeProgressColor = lerpColor(white, golden, timeProgress);

    Color mapTime = timeProgressColor;
    // 格式化字符串，插入颜色
    char text[256 * 16];
    sprintf(text,//"<b>"
                 "Tile BPM | <color=#%02X%02X%02X>%.2f</color>\n"
                 "Highest T BPM | <color=#%02X%02X%02X>%.2f</color>\n"
                 "Cur BPM | <color=#%02X%02X%02X>%.2f</color>\n"
                 "Avg BPM | <color=#%02X%02X%02X>%.2f</color>\n"
                 "KPS | <color=#%02X%02X%02X>%.2f</color>\n"
                 "Speed | %.2f\n\n"
                 "Music Time | <color=#%02X%02X%02X>%s</color> ~ <color=#%02X%02X%02X>%s</color>\n"
                 "Map Time | <color=#%02X%02X%02X>%s</color>\n"
                 "Attempt | %d\n"
                 "Check Point | %d\n\n"
                 "Progress | <color=#%02X%02X%02X>%.2f%%</color>\n"
                 "X-ACC | <color=#%02X%02X%02X>%.2f%%</color>\n"
                 "ACC | <color=#%02X%02X%02X>%.2f%%</color>\n\n"
                 "Perfect Combo | <color=#%02X%02X%02X>%d</color>\n"
                 "Timing | %.2f \n"
                 "Timing Scale | %d%%\n"
                 " \t\t\t\t\t \n"
                 "                 <size=42>"
                 "<color=#E69AF6>%d</color> "
                 "<color=#FF0000>%d</color> "
                 "<color=#FF3333>%d</color> "
                 "<color=#FFFF00>%d</color> "
                 "<color=#00FF00>%d</color> "
                 "<color=#FFFF00>%d</color> "
                 "<color=#FF3333>%d</color> "
                 "<color=#FF0000>%d</color> "
                 "<color=#00FFFF>%d</color> "
                 "<color=#E69AF6>%d</color>"
                 "</size>"
                 //"</b>"
                 ,
            
            // Tile BPM 颜色
            (int)(bpmColor.r * 255), (int)(bpmColor.g * 255), (int)(bpmColor.b * 255),
            curBPM,

            // Highest BPM 颜色
            (int)(bpmColor.r * 255), (int)(bpmColor.g * 255), (int)(bpmColor.b * 255),
            highestBPM,

            // Real BPM 颜色
            (int)(bpmColor.r * 255), (int)(bpmColor.g * 255), (int)(bpmColor.b * 255),
            realBPM,

            // Avg BPM 颜色
            (int)(bpmColor.r * 255), (int)(bpmColor.g * 255), (int)(bpmColor.b * 255),
            avgBPM,

            // KPS BPM 颜色
            (int)(bpmColor.r * 255), (int)(bpmColor.g * 255), (int)(bpmColor.b * 255),
            clickPerSecond,

            speed, 
            // 当前时间颜色
            (int)(timeProgressColor.r * 255), (int)(timeProgressColor.g * 255), (int)(timeProgressColor.b * 255),
            currentTimeFormatted.c_str(),

            // 总时间颜色
            (int)(golden.r * 255), (int)(golden.g * 255), (int)(golden.b * 255),
            totalLengthFormatted.c_str(),

            // 关卡时间颜色
            (int)(mapTime.r * 255), (int)(mapTime.g * 255), (int)(mapTime.b * 255),
            mapTimeFormatted.c_str(),

            frequency, checkpoints,

            // Progress 颜色
            (int)(progressColor.r * 255), (int)(progressColor.g * 255), (int)(progressColor.b * 255),
            progress * 100,

            // X-ACC 颜色
            (int)(xAccColor.r * 255), (int)(xAccColor.g * 255), (int)(xAccColor.b * 255),
            percentXAcc * 100,

            // ACC 颜色
            (int)(accColor.r * 255), (int)(accColor.g * 255), (int)(accColor.b * 255),
            percentAcc * 100,

            // Combo 颜色
            (int)(comboColor.r * 255), (int)(comboColor.g * 255), (int)(comboColor.b * 255),
            PerfectCombo,

            ms, margin, failOverloadNum, tooEarlyNum, veryEarlyNum, earlyPerfectNum, perfectNum,
            latePerfectNum, veryLateNum, tooLateNum, multipressNum, failMissNum);
            
        //char result[1024 * 16];
            /*
            sprintf(result, "\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t                  <b><size=30><color=#E69AF6>%d</color> <color=#FF0000>%d</color> <color=#FF3333>%d</color> <color=#FFFF00>%d</color> <color=#00FF00>%d</color> <color=#FFFF00>%d</color> <color=#FF3333>%d</color> <color=#FF0000>%d</color> <color=#00FFFF>%d</color> <color=#E69AF6>%d</color></size></b>",
            failOverloadNum, tooEarlyNum, veryEarlyNum, earlyPerfectNum, perfectNum,
            latePerfectNum, veryLateNum, tooLateNum, multipressNum, failMissNum);
            */
            
     //   AddText(result,40,930,30,Color(1.0f,1.0f,1.0f),nullptr,UpperCenter);
        AddText(text,250,30,40,Color(1.0f,1.0f,1.0f),Color(0.f,0.f,0.f,0.5f),Vector2(2,2),UpperCenter);
        old_OnGUI(instance);
    } else  {
        if (devValue == true) {
            AddText(dev,70,0,30,Color(1.0f,1.0f,1.0f),Color(0,0,0),Vector2(1.5,-1.5));
        old_OnGUI(instance);
        } else {
        AddText(none,70,0,30,Color(1.0f,1.0f,1.0f),Color(0,0,0),Vector2(1.5,-1.5));
        old_OnGUI(instance);
    }
    }
}


//显示
void AddText(string text, float x, float y, int textSize, Color color, 
            Color shadowColor, Vector2 shadowOffset, TextAnchor alignment) 
{
    static Class GUIStyleClass = Class("UnityEngine", "GUIStyle");
    static Class GUIContentClass = Class("UnityEngine", "GUIContent");
    
    Il2CppObject* mainStyle = GUIStyleClass.CreateNewObjectParameters();
    
    auto SetStyleProperties = [&](Il2CppObject* style) {
        // 字体样式
        Method<void> setFontStyle = GUIStyleClass.GetMethod("set_fontStyle");
        setFontStyle[style].Call(0); // FontStyle.Normal
        
        // 字体大小
        Method<void> setFontSize = GUIStyleClass.GetMethod("set_fontSize");
        setFontSize[style].Call(textSize);
        
        // 对齐方式
        Method<void> setAlignment = GUIStyleClass.GetMethod("set_alignment");
        setAlignment[style].Call(alignment);
        
        // 设置字体
        UnityEngine::Object* Onstants = getFieldValue<UnityEngine::Object *>("","RDConstants","internalData");
        Field<UnityEngine::Object*> chineseFont = Class("","RDConstants").GetField("chineseFont");
        Field<UnityEngine::Object*> koreanFont = Class("","RDConstants").GetField("koreanFont");
        Method<void> setFont = GUIStyleClass.GetMethod("set_font");
        String* currentLanguage = Persistence_GetLanguageMet();
        std::string currentLang = currentLanguage ? currentLanguage->str() : "";

        // 根据实际内容判断语言
        if (currentLang != "ChineseSimplified") {
            setFont[style].Call(koreanFont[Onstants].Get());
        } else {
            setFont[style].Call(chineseFont[Onstants].Get());
        }
    };

    // 初始化主样式
    SetStyleProperties(mainStyle);

    // 颜色设置函数
    auto SetStyleColor = [&](Il2CppObject* style, Color color) {
        Method<Il2CppObject*> getNormal = GUIStyleClass.GetMethod("get_normal");
        Il2CppObject* normalState = getNormal[style].Call();
        Method<void> setTextColor = Class("UnityEngine", "GUIStyleState").GetMethod("set_textColor");
        setTextColor[normalState].Call(color);
    };
    
    // 强制覆盖阴影颜色为纯黑（带透明度控制）
    shadowColor = Color{0.0f, 0.0f, 0.0f, shadowColor.a}; // 固定RGB为黑色，保留原有透明度

    // 设置阴影颜色（增强型方法）
    auto ForceSetShadowColor = [&](Il2CppObject* style) {
        // 获取GUIStyleState
        Method<Il2CppObject*> getNormal = GUIStyleClass.GetMethod("get_normal");
        Il2CppObject* normalState = getNormal[style].Call();
        
        // 强制设置所有颜色通道
        Method<void> setTextColor = Class("UnityEngine", "GUIStyleState").GetMethod("set_textColor");
        setTextColor[normalState].Call(shadowColor);
        
        // 清除可能覆盖颜色的其他状态
        Method<void> setBackground = Class("UnityEngine", "GUIStyleState").GetMethod("set_background");
        setBackground[normalState].Call(nullptr); // 移除背景纹理
    };


    // 设置主文本颜色
    SetStyleColor(mainStyle, color);

    // 计算文本实际尺寸
    Method<Vector2> calcSize = GUIStyleClass.GetMethod("CalcSize");
    Il2CppObject* content = GUIContentClass.CreateNewObjectParameters(CreateMonoString(text));
    Vector2 textSizeVec = calcSize[mainStyle].Call(content);

    // 根据对齐方式调整原点坐标
    float originX = x;
    float originY = y;
    switch (alignment) {
        case 0: /* UpperLeft */ break;
        case 1: originX -= textSizeVec.x/2; break;    // UpperCenter
        case 2: originX -= textSizeVec.x; break;       // UpperRight
        case 3: originY -= textSizeVec.y/2; break;     // MiddleLeft
        case 4: originX -= textSizeVec.x/2;            // MiddleCenter
               originY -= textSizeVec.y/2; break;
        case 5: originX -= textSizeVec.x;              // MiddleRight
               originY -= textSizeVec.y/2; break;
        case 6: originY -= textSizeVec.y; break;       // LowerLeft
        case 7: originX -= textSizeVec.x/2;             // LowerCenter
               originY -= textSizeVec.y; break;
        case 8: originX -= textSizeVec.x;               // LowerRight
               originY -= textSizeVec.y; break;
    }

    // 创建阴影样式（完全独立的属性设置）
    Il2CppObject* shadowStyle = GUIStyleClass.CreateNewObjectParameters();
    SetStyleProperties(shadowStyle); // 重用属性设置函数
    SetStyleColor(shadowStyle, shadowColor);
    ForceSetShadowColor(shadowStyle); // 使用强化版颜色设置

    // 创建绘制区域
    Structures::Unity::Rect mainRect(originX, originY, textSizeVec.x, textSizeVec.y);
    Structures::Unity::Rect shadowRect(
        originX + shadowOffset.x,
        originY + shadowOffset.y,
        textSizeVec.x,
        textSizeVec.y
    );

    // 执行绘制
    Method<void> guiLabel = Class("UnityEngine", "GUI").GetMethod("Label", {"position", "text", "style"});
    //CppString* monoText = CreateMonoString(text);
    
    guiLabel.Call(shadowRect, CreateMonoString(text), shadowStyle); // 先绘制阴影
    guiLabel.Call(mainRect, CreateMonoString(text), mainStyle);     // 再绘制主文本
}

    Il2CppObject* LoadSystemFont(const std::string& fontName, int fontSize) {
    // 获取Font类引用
    static Class FontClass = Class("UnityEngine", "Font");
    
    // 调用CreateDynamicFontFromOSFont方法
    static Method<Il2CppObject*> createMethod = FontClass.GetMethod(
        "CreateDynamicFontFromOSFont", 
        {"System.String", "System.Int32"}
    );
    
    
    // 创建字体对象
    //Il2CppString* il2cppFontName = CreateMonoString(fontName);
    return createMethod.Call(nullptr, CreateMonoString(fontName), fontSize);
}

Il2CppObject* LoadResourceFont(const std::string& resourcePath) {
    // 获取Resources类
    static Class ResourcesClass = Class("UnityEngine", "Resources");
    
    // 调用Resources.Load方法
    static Method<Il2CppObject*> loadMethod = ResourcesClass.GetMethod(
        "Load", 
        {"System.String", "System.Type"}
    );
    
    // 获取Font类
    static Class FontClass = Class("UnityEngine", "Font");
    
    // 获取Font类型
    static Il2CppType* fontType = &FontClass.GetClass()->byval_arg;
    
    return loadMethod.Call(nullptr, CreateMonoString(resourcePath), fontType);
}


Il2CppObject* GetDefaultFont() {
    // 获取内置默认字体（如Arial）
    static Class FontClass = Class("UnityEngine", "Font");
    static Field<Il2CppObject*> defaultFontField = FontClass.GetField("defaultFont");
    return defaultFontField.Get();
}


std::string secondsToMMSS(float seconds) {
    int minutes = static_cast<int>(seconds) / 60;
    int secs = static_cast<int>(seconds) % 60;

    // 使用 std::ostringstream 格式化字符串
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << secs;

    return oss.str();
}

Color lerpColor(const Color& a, const Color& b, float t) {
    t = std::max(0.0f, std::min(1.0f, t));
    return Color(
        a.r + (b.r - a.r) * t,
        a.g + (b.g - a.g) * t,
        a.b + (b.b - a.b) * t
    );
}

//自定义dlc扩展包路径
String (*old_dlcPath)(UnityEngine::Object *);
String* dlc(UnityEngine::Object *instance) {
    return CreateMonoString("/sdcard/DLC/2.4.5/NeoCosmos");
    
}
//开启debug
bool (*old_debug)(UnityEngine::Object *);
bool debug(UnityEngine::Object *instance) {
    return true;
}
bool (*old_isMobile)(UnityEngine::Object *);
bool IsMobile(UnityEngine::Object *instance) {
        Method<String*> sceneName = Class("","ADOBase").GetMethod("get_sceneName");
        if (sceneName.Call()->str() == "scnTaroMenu0" || sceneName.Call()->str() == "scnTaroMenu1" || sceneName.Call()->str() == "scnTaroMenu2" || sceneName.Call()->str() == "scnTaroMenu3") {
            return false;
        } else {
                return old_isMobile(instance);
        }
}

void (*old_RecoverSaveDataFromSteamAchievements)(UnityEngine::Object *);
void fuck() {
    Field<String*> sceneToLoadField = Class("", "GCS").GetField("sceneToLoad");
    sceneToLoadField.Set(CreateMonoString("scnEditor"));
}

void (*old_scrMistakesManager_AddHit)(UnityEngine::Object *);
void AddHitMet(UnityEngine::Object *instance, HitMargin hit) {
    old_scrMistakesManager_AddHit(instance);
    switch (hit) {
        case TooEarly:
            score += 30;
            break;
        case TooLate:
            score += 30;
            break;
        case VeryEarly:
            score += 75;
            break;
        case VeryLate:
            score += 75;
            break;
        case EarlyPerfect:
            score += 150;
            break;
        case LatePerfect:
            score += 150;
            break;
        case Perfect:
            score += 300;
            break;
        default:
            
            break;
    }

    if (hit == Multipress) {
        score -= 50;
    }

    if (hit == FailMiss) {
        score -= 100;
    }

    if (hit == FailOverload) {
        score -= 200;
    }
    
        if (hit == Perfect) {
            PerfectCombo++;
            } else {
                PerfectCombo = 0;
            }
}

bool (*old_Bool_isMobile)(UnityEngine::Object *);
bool Bool_IsMobile(bool value) {
        return value;
}

bool (*old_RDColorPickerPopup_get_UsesAlpha)(UnityEngine::Object *);
bool UsesAlphaMet(UnityEngine::Object *instance) {
    return true;
}

//屏蔽判定文本
void (*old_scrController_ShowHitText)(UnityEngine::Object *,HitMargin,Vector3,float);
void ShowHitTextMet(UnityEngine::Object *instance,HitMargin hitMargin,Vector3 position,float angle) {
    if (hitMargin != Perfect) {
    old_scrController_ShowHitText(instance, hitMargin, position, angle);
    }
}



DifficultyUIMode (*old_scrMisc_DetermineDifficultyUIMode)();
DifficultyUIMode DetermineDifficultyUIModeMet() {
    return ShowAll;
}

void (*old_scrMisc_GetHitMargin)();
void GetHitMarginMet(float hitangle, float refangle, bool isCW, float bpmTimesSpeed, float conductorPitch) {
    old_scrMisc_GetHitMargin();
    float angle = (hitangle - refangle) * (isCW ? 1 : -1) * 57.29578f;
    ms = angle / 180 / bpmTimesSpeed / conductorPitch * 60000;
}

bool (*old_scrPlanet_GetMultipressPenalty)();
bool GetMultipressPenaltyMet() {
    return false;
}

/*
没用的
void (*old_scrController_Awake)(UnityEngine::Object *);
void AwakeMet(UnityEngine::Object *instance) {
    auto  ADOBaseClass = Class("","ADOBase");
    Method<bool> GetisMobile = ADOBaseClass.GetMethod("get_isMobile");
    Bool_IsMobile(false);
    old_scrController_Awake(instance);
    Bool_IsMobile(true);
}

void (*old_scrRing_Update)(UnityEngine::Object *);
void UpdateMet(UnityEngine::Object *instance) {
    return;
}

void (*old_scrPlanet_SetRingColor)(UnityEngine::Object *);
void SetRingColorMet(UnityEngine::Object *instance, Color color) {
    Color(0.0f,0.0f,0.0f,0.0f);
    return;
}
int (*old_PropertyInfo_Validate)(UnityEngine::Object *);
int IntValidateMet(UnityEngine::Object *instance, int value) {
    return value;
}
*/

template <typename T>
T getFieldValue(std::string NS,std::string className,std::string fieldName,Il2CppObject *instance) {
    Class clazz = Class(NS,className);
    Field<T> field = clazz.GetField(fieldName);
    if (instance == nullptr) return field.Get();
    return field[instance].Get();
}

template <typename T>
T callMethod(std::string nameSpace,std::string className,std::string methodName,Il2CppObject *instance) {
    Class clazz = Class(nameSpace,className);
    Method<T> method = clazz.GetMethod(methodName);
    if (instance == nullptr) return method.Call();
    return method[instance].Call();
}

// 定义模板函数 Last，接受通用指针
template <typename T>
T Last(T* ptr) {
    if (ptr == nullptr) {
        throw std::invalid_argument("Pointer is null");
    }
    return *ptr;
}

// 定义模板函数 Last，接受通用引用
template <typename T>
T Last(T& ref) {
    return ref;
}

std::string FormatFloatToString(float value, std::ostringstream& ss) {
    ss.str("");
    ss.clear();
    ss << std::fixed << std::setprecision(2) << value;
    return ss.str();
}
std::string BoolToStr(bool value) {
    return value ? "开启" : "关闭";
}

std::string DifficultyToStr(Difficulty  value) {
    if (value == Lenient) {
        return "宽松"; //Lenient
    } else if (value == Normal) {
        return "标准"; //Normal
    } else if (value == Strict) {
        return "严格"; //Strict
    } else {
        return "无"; //Unknown
    }
}

void start() {
    /*
    Image ass = Image("Assembly-CSharp");
    auto classes = ass.GetClasses();
    for (int i = 0; i < classes.size(); ++i) {
        __android_log_print(6,"TAG","class:%s",classes[i].str().c_str());
    }

    auto fields = Class("ADOFAI","LevelData").GetFields();
    for (int i = 0; i < fields.size(); ++i) {
        __android_log_print(6,"TAG","field:%s",fields[i].str().c_str());
    }
    */
    __android_log_print(6,"TAG","start");
    BNM_try

                        scrPlanet = Class("","scrPlanet");
                auto move = scrPlanet.GetMethod("MoveToNextFloor");
                HOOK(move,MoveToNextFloor, old_MoveToNextFloor);
                auto scrPlanetGetMultipressPenaltyClass = scrPlanet.GetMethod("GetMultipressPenalty");
                HOOK(scrPlanetGetMultipressPenaltyClass, GetMultipressPenaltyMet, old_scrPlanet_GetMultipressPenalty);                
                auto start = Class("","CustomLevel").GetMethod("Play");
                //auto start = Class("","scnGame").GetMethod("Play");
                HOOK(start, startPlay,old_start);
                                auto openlevelpath = Class("SFB","StandaloneFileBrowser").GetMethod("OpenFilePanel");
                HOOK(openlevelpath, openFilePanel,old_SFB_StandaloneFileBrowser_OpenFilePanel);
                auto savelevelpath = Class("SFB","StandaloneFileBrowser").GetMethod("SaveFilePanelAsync");
                HOOK(savelevelpath, saveFilePanelAsync, old_SFB_StandaloneFileBrowser_SaveFilePanelAsync);
                auto autoClass = Class("","scrShowIfDebug").GetMethod("Update");
                //InvokeHook(autoClass, scrShowIfDebug,old_scrShowIfDebug_Update);
                auto startClass = Class("","ADOStartup").GetMethod("Startup");
                HOOK(startClass, adofaiStart,old_ADOStartup_Startup);
                auto updatevalue = Class("","scrController").GetMethod("PlayerControl_Update");
                HOOK(updatevalue, PlayerUpdate,old_scrController_PlayerControl_Update);
                auto loadLevel = Class("","scrController").GetMethod("Restart");
                HOOK(loadLevel, newRestart,old_scrController_Restart);
                auto quittomenu = Class("","scrController").GetMethod("QuitToMainMenu");
                HOOK(quittomenu, load,old_scrController_QuitToMainMenu);
                auto AddHitClass = Class("","scrMistakesManager").GetMethod("AddHit");
                HOOK(AddHitClass, AddHitMet,old_scrMistakesManager_AddHit);
                auto scrControllerClass_GetShowHitTextMethod = Class("","scrController").GetMethod("ShowHitText");
                HOOK(scrControllerClass_GetShowHitTextMethod, ShowHitTextMet,old_scrController_ShowHitText);
                auto RDColorPickerPopupClass = Class("ADOFAI","RDColorPickerPopup").GetMethod("get_UsesAlpha");
                HOOK(RDColorPickerPopupClass, UsesAlphaMet,old_RDColorPickerPopup_get_UsesAlpha);
                auto scrMisc_DetermineDifficultyUIMode = Class("","scrMisc").GetMethod("DetermineDifficultyUIMode");
                HOOK(scrMisc_DetermineDifficultyUIMode, DetermineDifficultyUIModeMet, old_scrMisc_DetermineDifficultyUIMode);
                auto scrMisc_GetHitMargin = Class("","scrMisc").GetMethod("GetHitMargin");
                HOOK(scrMisc_GetHitMargin, GetHitMarginMet, old_scrMisc_GetHitMargin);
                
                /*
                auto PropertyInfoClass = Class("","PropertyInfo").GetMethod("Validate");
                HOOK(PropertyInfoClass, IntValidateMet,old_PropertyInfo_Validate);
                /*
                auto AwakeClass = Class("","scrController").GetMethod("Awake");
                HOOK(AwakeClass, AwakeMet,old_scrController_Awake);
                auto scrRingClass = Class("","scrRing").GetMethod("Update");
                HOOK(scrRingClass, UpdateMet,old_scrRing_Update);
                auto scrPlanetCalss = Class("","scrPlanet").GetMethod("SetRingColor");
                HOOK(scrPlanetCalss, SetRingColorMet,old_scrPlanet_SetRingColor);
                /*
                auto openlevelpath = Class("SFB","StandaloneFileBrowser").GetMethod("OpenFilePanel");
                HOOK(openlevelpath, openFilePanel,old_SFB_StandaloneFileBrowser_OpenFilePanel);
                auto savelevelpath = Class("SFB","StandaloneFileBrowser").GetMethod("SaveFilePanelAsync");
                HOOK(savelevelpath, saveFilePanelAsync, old_SFB_StandaloneFileBrowser_SaveFilePanelAsync);
                */
                auto Persistence_GetLanguage = Class("","Persistence").GetMethod("GetLanguage");
                HOOK(Persistence_GetLanguage, Persistence_GetLanguageMet, old_Persistence_GetLanguage);
                auto Persistence_GetLastOpenedLevel = Class("","Persistence").GetMethod("GetLastOpenedLevel");
                //HOOK(Persistence_GetLastOpenedLevel, Persistence_GetLastOpenedLevelMet, old_Persistence_GetLastOpenedLevel);
                 auto RDString_GetMethod = Class("","RDString").GetMethod("Get");
                HOOK(RDString_GetMethod, RDString_Get, old_RDString_Get);
                
                Class scnEditor = Class("","scnEditor");
                auto OnGUIMethod = scnEditor.GetMethod("OnGUI");
                auto reset = scnEditor.GetMethod("ResetScene");
                InvokeHook(OnGUIMethod,OnGUI,old_OnGUI);
                /*
                auto dlcPath = Class("","GCNS").GetMethod("get_NeoCosmosLoadPath");
                HOOK(dlcPath, dlc,old_dlcPath);
                */
                auto isMobile = Class("","ADOBase").GetMethod("get_isMobile");
                HOOK(isMobile, IsMobile,old_isMobile);
                HOOK(isMobile, Bool_IsMobile,old_Bool_isMobile);
                auto GetRecoverSaveDataFromSteamAchievements = Class("","Persistence").GetMethod("RecoverSaveDataFromSteamAchievements");
                HOOK(GetRecoverSaveDataFromSteamAchievements, fuck,old_RecoverSaveDataFromSteamAchievements);
                //auto GetDebug = Class("","RDC").GetMethod("get_debug");
                // HOOK(GetDebug, debug,old_debug);
                        BNM_catch(exception)
                        auto name = exception.ClassName();
                            __android_log_print(3,"114514","%s", name.c_str());
    BNM_end_try

}
