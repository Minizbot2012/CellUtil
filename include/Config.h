#pragma once
namespace MPL::Config
{
    class StatData : public REX::Singleton<StatData>
    {
    public:
        SKSE::RegistrationSet<RE::TESObjectCELL*> cellLoad{ "OnCellChange"sv };
    };
}  // namespace MPL::Config

namespace rfl
{
    template <>
    struct Reflector<RE::FormID>
    {
        using ReflType = std::string;
        static ReflType from(const RE::FormID& v)
        {
            auto frm = RE::TESForm::LookupByID(v);
            return std::format("{:06X}:{}", frm->GetLocalFormID(), frm->sourceFiles.array->front()->GetFilename());
        }
        static RE::FormID to(const ReflType& v)
        {
            auto loc = v.find(":");
            if (loc != std::string::npos)
            {
                auto lfid = strtoul(v.substr(0, loc).c_str(), nullptr, 16);
                auto file = v.substr(loc + 1);
                auto dh = RE::TESDataHandler::GetSingleton();
                return dh->LookupFormID(lfid, file);
            }
            else {
                return RE::TESForm::LookupByEditorID(v)->GetFormID();
            }
        }
    };
}  // namespace rfl