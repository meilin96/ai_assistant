#ifdef TOOLS_ENABLED

#include "ai_assistant_plugin.h"
#include "ai_assistant_panel.h"

#include "editor/inspector/editor_context_menu_plugin.h"

class AIAssistantSceneTreeContextMenuPlugin : public EditorContextMenuPlugin {
	GDCLASS(AIAssistantSceneTreeContextMenuPlugin, EditorContextMenuPlugin);

	AIAssistantPanel *panel = nullptr;

protected:
	static void _bind_methods() {
		ClassDB::bind_method(D_METHOD("_on_mention_selected", "selection"), &AIAssistantSceneTreeContextMenuPlugin::_on_mention_selected);
	}

public:
	virtual void get_options(const Vector<String> &p_paths) override {
		if (p_paths.is_empty()) {
			return;
		}

		add_context_menu_item(TTR("Mention in AI Assistant"), callable_mp(this, &AIAssistantSceneTreeContextMenuPlugin::_on_mention_selected), Ref<Texture2D>());
	}

protected:
	void _on_mention_selected(const Variant &p_selection) {
		(void)p_selection;
		if (panel) {
			panel->insert_mention_of_selected_node();
		}
	}

public:
	void set_panel(AIAssistantPanel *p_panel) {
		panel = p_panel;
	}
};

void AIAssistantPlugin::_bind_methods() {}

AIAssistantPlugin::AIAssistantPlugin() {
	panel = memnew(AIAssistantPanel);
	add_control_to_dock(DOCK_SLOT_RIGHT_UL, panel);

	Ref<AIAssistantSceneTreeContextMenuPlugin> typed_plugin = memnew(AIAssistantSceneTreeContextMenuPlugin);
	typed_plugin->set_panel(panel);
	scene_tree_menu_plugin = typed_plugin;
	add_context_menu_plugin(EditorContextMenuPlugin::CONTEXT_SLOT_SCENE_TREE, scene_tree_menu_plugin);
}

AIAssistantPlugin::~AIAssistantPlugin() {
	if (scene_tree_menu_plugin.is_valid()) {
		remove_context_menu_plugin(scene_tree_menu_plugin);
		scene_tree_menu_plugin.unref();
	}
}

#endif // TOOLS_ENABLED
