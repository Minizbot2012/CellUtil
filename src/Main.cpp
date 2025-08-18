#include <Config.h>
#include <Hooks.h>
#include <Papyrus.h>
#if defined(SKYRIM_AE) || defined(SKYRIM_SE)
extern "C" DLLEXPORT auto SKSEPlugin_Version = []() {
    SKSE::PluginVersionData v;
    v.PluginVersion({ 1, 0, 0, 0 });
    v.PluginName("CLUtil");
    v.AuthorName("mini");
    v.UsesAddressLibrary();
    v.UsesNoStructs();
    return v;
}();
#elif defined(SKYRIM_VR)
extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
{
    a_info->infoVersion = SKSE::PluginInfo::kVersion;
    a_info->name = "CLUtil";
    a_info->version = 0x10000000;
    if (a_skse->IsEditor())
    {
        return false;
    }
    const auto ver = a_skse->RuntimeVersion();
    if (ver < SKSE::RUNTIME_VR_1_4_15)
    {
        return false;
    }
    return true;
};
#endif
void Serialize(SKSE::SerializationInterface* ser)
{
    MPL::Config::StatData::GetSingleton()->cellLoad.Save(ser, 'CLCH', 0x1);
}

void Deserialize(SKSE::SerializationInterface* ser)
{
    uint32_t type;
    uint32_t version;
    uint32_t len;
    while (ser->GetNextRecordInfo(type, version, len))
    {
        switch (type)
        {
        case 'CLCH':
            MPL::Config::StatData::GetSingleton()->cellLoad.Load(ser);
            break;
        default:
            break;
        }
    }
}

void Revert(SKSE::SerializationInterface* ser)
{
    MPL::Config::StatData::GetSingleton()->cellLoad.Revert(ser);
}

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
    SKSE::Init(a_skse);
    logger::info("Game version : {}", a_skse->RuntimeVersion().string());
    SKSE::GetPapyrusInterface()->Register(MPL::Papyrus::Bind);
    auto ser = SKSE::GetSerializationInterface();
    ser->SetUniqueID('CLTL');
    ser->SetSaveCallback(Serialize);
    ser->SetLoadCallback(Deserialize);
    ser->SetRevertCallback(Revert);
    MPL::Hooks::Install();
    return true;
}