#pragma once

#ifdef TOOLS_ENABLED

#include "editor/plugins/editor_plugin.h"

class AIAssistantPanel;
class EditorContextMenuPlugin;

class AIAssistantPlugin : public EditorPlugin {
	GDCLASS(AIAssistantPlugin, EditorPlugin);

	AIAssistantPanel *panel = nullptr;
	Ref<EditorContextMenuPlugin> scene_tree_menu_plugin;

protected:
	static void _bind_methods();

public:
	virtual String get_plugin_name() const override { return "AIAssistant"; }

	AIAssistantPlugin();
	~AIAssistantPlugin();
};

#endif // TOOLS_ENABLED
