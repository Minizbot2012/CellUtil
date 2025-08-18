#pragma once
#include <Config.h>
namespace MPL::Papyrus
{
#define STATIC_ARGS RE::StaticFunctionTag*
    std::string GetRegion(RE::StaticFunctionTag*, RE::TESObjectCELL* cl) {
        if(cl->extraList.HasType<RE::ExtraCellSkyRegion>()) {
            auto dat = cl->extraList.GetByType<RE::ExtraCellSkyRegion>();
            return dat->skyRegion->GetFormEditorID();
        }
        else {
            return "";
        }
    }
    void ChangeRegion(RE::StaticFunctionTag*, RE::TESObjectCELL* cl, std::string region) {
        if(cl->extraList.HasType<RE::ExtraCellSkyRegion>()) {
            auto dat = cl->extraList.GetByType<RE::ExtraCellSkyRegion>();
            dat->skyRegion = RE::TESForm::LookupByEditorID<RE::TESRegion>(region);
        } else {
            auto dat = RE::BSExtraData::Create<RE::ExtraCellSkyRegion>();
            dat->skyRegion = RE::TESForm::LookupByEditorID<RE::TESRegion>(region);
            cl->extraList.Add(dat);
        }
    }
    void RegisterForOnCellLoad(RE::StaticFunctionTag*, RE::TESForm* listener) {
        MPL::Config::StatData::GetSingleton()->cellLoad.Register(listener);
    }
#undef STATIC_ARGS
    bool Bind(RE::BSScript::IVirtualMachine* vm)
    {
        vm->RegisterFunction("GetRegion", "CLUtil", GetRegion);
        vm->RegisterFunction("ChangeRegion", "CLUtil", ChangeRegion);
        vm->RegisterFunction("RegisterForCellload", "CLUtil", RegisterForOnCellLoad);
        return true;
    }
}  // namespace vlrp::papyrus