#ifdef CLIENT
#include "hooks/client/UI.hpp"

#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/runtime/utility/InlineHook.hpp>
#include <amethyst/runtime/events/RenderingEvents.hpp>
#include <amethyst/runtime/events/UiEvents.hpp>

#include <mc/src-client/common/client/gui/ScreenView.hpp>
#include <mc/src-client/common/client/gui/screens/ScreenController.hpp>
#include <mc/src-client/common/client/gui/screens/controllers/StartMenuScreenController.hpp>
#include <mc/src/common/locale/I18n.hpp>

namespace Amethyst::ClientHooks::UIHooks {
	Amethyst::InlineHook<decltype(&ScreenView::setupAndRender)> _ScreenView_setupAndRender;
	void ScreenView_setupAndRender(ScreenView* self, MinecraftUIRenderContext& ctx) {
		auto& bus = Amethyst::GetEventBus();
		BeforeRenderUIEvent ev(*self, ctx);
		bus.Invoke(ev);
		_ScreenView_setupAndRender(self, ctx);
		AfterRenderUIEvent afterEv(*self, ctx);
		bus.Invoke(afterEv);
	}

	Amethyst::InlineHook<decltype(&ScreenController::_handleButtonEvent)> _ScreenController__handleButtonEvent;
	ui::ViewRequest ScreenController__handleButtonEvent(ScreenController* screen, ScreenEvent& event) {
		ui::ViewRequest result = _ScreenController__handleButtonEvent(screen, event);
		UIButtonHandleEvent ev(event);
		Amethyst::GetEventBus().Invoke(ev);
		return result;
	}

	Amethyst::InlineHook<decltype(&StartMenuScreenController::_registerBindings)> _StartMenuScreenController__registerBindings;
	void StartMenuScreenController__registerBindings(StartMenuScreenController* self) {
		_StartMenuScreenController__registerBindings(self);
		auto& context = Amethyst::GetContext();
		const Amethyst::Mod* ownMod = Amethyst::GetOwnMod();
		std::string versionStr;
		if (ownMod->mInfo->Version.prerelease_tag() == "dev")
			versionStr = std::format("{}", "§uAmethyst Runtime (DEV)§r");
		else
			versionStr = std::format("Amethyst Runtime v{}", ownMod->mInfo->Version.to_string());

		// Register '#amethyst_version' binding
		self->bindString(StringHash("#amethyst_version"), [versionStr]() {
			return versionStr;
		}, []() {
			return true;
		});

		// Register '#mods_loaded' binding
		self->bindString(StringHash("#mods_loaded"), [&context]() -> std::string {
			// Not beautiful but works
			auto* mod = GetOwnMod();
			if (!mod)
				return "Reloading...";

			auto* importer = mod->GetImporter();
			if (!importer || !importer->IsResolved() || !context.mModLoader) {
				return "Reloading...";
			}

			size_t count = context.mModLoader->GetModCount();
			std::string modsLoadedLocalized = "text.amethyst.mods_loaded"_i18n;
			bool plural = (count != 1);
			std::string pluralSuffix = plural ? "s" : "";
			return std::vformat(modsLoadedLocalized, std::make_format_args(count, pluralSuffix, pluralSuffix));
		}, []() {
			return true;
		});
	}

	void Initialize() {
		auto& hooks = Amethyst::GetHookManager();
		HOOK(ScreenView, setupAndRender);
		HOOK(ScreenController, _handleButtonEvent);
		HOOK(StartMenuScreenController, _registerBindings);
	}
}
#endif