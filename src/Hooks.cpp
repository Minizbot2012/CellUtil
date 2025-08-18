#include <Hooks.h>
namespace MPL::Hooks
{
    struct InitCell
    {
        using Target = RE::PlayerCharacter;
        static inline void thunk(Target* a_ref, RE::TESObjectCELL* cl)
        {
            func(a_ref, cl);
            if(cl!=nullptr) {
                logger::info("CELL CHANGE into {:X}:{}", cl->GetLocalFormID(), cl->sourceFiles.array->front()->GetFilename());
                Config::StatData::GetSingleton()->cellLoad.QueueEvent(cl);
            }
        }
        static inline REL::Relocation<decltype(thunk)> func;
        static inline constexpr std::size_t index{ 0x98 };
    };
    void Install()
    {
        stl::install_hook<InitCell>();
    };
}  // namespace MPL::Hooks