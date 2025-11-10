import { GetRef, Panel, PanelProps, StackPanel, UiFile, Variable, createFile, createMinecraftElement } from "Regolith-Generators";

Deno.exit(0); // stuff below is WIP

const inventoryScreen = new UiFile("crafting");

interface TopTabProps extends PanelProps {
    $is_left_most_tab: boolean;
    $tab_view_binding_name: Variable<string>;
    $tab_icon: Variable<string>;
    $toggle_group_forced_index: Variable<number>; 

    $toggle_binding_type: Variable<string>,
    $toggle_state_binding_name: Variable<string>,

    $top_tab_tts_name: Variable<string>

    $focus_id: Variable<string>;
    $focus_override_left: Variable<string>;
    $focus_override_right: Variable<string>;
    $focus_override_up: Variable<string>;

    "$unchecked_default_image": "textures/ui/TabTopBackLeftMost",
    "$unchecked_hover_image": "textures/ui/TabTopBackLeftMostHover",
    "$unchecked_locked_image": "textures/ui/TabTopBackLeftMost",
    "$unchecked_locked_hover_image": "textures/ui/TabTopBackLeftMost",

    "$checked_default_image": "textures/ui/TabTopFrontLeftMost",
    "$checked_hover_image": "textures/ui/TabTopFrontLeftMostHover",
    "$checked_locked_image": "textures/ui/TabTopFrontLeftMost",
    "$checked_locked_hover_image": "textures/ui/TabTopFrontLeftMost",
}

const ConstructionTab = GetRef<TopTabProps>("crafting", "construction_tab");

const TopTab = GetRef<TopTabProps>("crafting", "top_tab");

// inventoryScreen.addControl("construction_tab", )

inventoryScreen.addControl("test_tab", <TopTab 
    $is_left_most_tab={false}
    $tab_view_binding_name="test_tab_toggle" 
    $toggle_group_forced_index={8} 
    $tab_icon="crafting.nature_icon" 
    $toggle_binding_type="global"
    $toggle_state_binding_name="#is_left_tab_test"
    $top_tab_tts_name="craftingScreen.tab.test"
    $focus_id="test_tab"
    $focus_override_left="help_button"
    $focus_override_right="construction_tab"
    $focus_override_up="FOCUS_OVERRIDE_STOP"

    $unchecked_default_image="textures/ui/TabTopBackLeftMost"
    $unchecked_hover_image="textures/ui/TabTopBackLeftMostHover"
    $unchecked_locked_image="textures/ui/TabTopBackLeftMost"
    $unchecked_locked_hover_image="textures/ui/TabTopBackLeftMost"

    $checked_default_image="textures/ui/TabTopFrontLeftMost"
    $checked_hover_image="textures/ui/TabTopFrontLeftMostHover"
    $checked_locked_image="textures/ui/TabTopFrontLeftMost"
    $checked_locked_hover_image="textures/ui/TabTopFrontLeftMost"

    variables={[
      {
        requires: "$animate",
        $anims: [ "@crafting.tab_wait_anim" ],
        $offset: "$top_tab_anim_start"
      }
    ]}
/>)

inventoryScreen.addControl("construction_tab", <TopTab 
    $is_left_most_tab
    $tab_view_binding_name="construction_tab_toggle" 
    $tab_icon="crafting.construction_icon" 
    $toggle_group_forced_index="$construction_index"

    $toggle_binding_type="global"
    $toggle_state_binding_name="#is_left_tab_construct" // purposefully "construct"

    $top_tab_tts_name="craftingScreen.tab.construction"
    
    $focus_id="construction_tab"
    $focus_override_left="help_button"
    $focus_override_right="equipment_tab"
    $focus_override_up="FOCUS_OVERRIDE_STOP"

    $unchecked_default_image="textures/ui/TabTopBackLeftMost"
    $unchecked_hover_image="textures/ui/TabTopBackLeftMostHover"
    $unchecked_locked_image="textures/ui/TabTopBackLeftMost"
    $unchecked_locked_hover_image="textures/ui/TabTopBackLeftMost"

    $checked_default_image="textures/ui/TabTopFrontLeftMost"
    $checked_hover_image="textures/ui/TabTopFrontLeftMostHover"
    $checked_locked_image="textures/ui/TabTopFrontLeftMost"
    $checked_locked_hover_image="textures/ui/TabTopFrontLeftMost"

    variables={[
      {
        requires: "$animate",
        $anims: [ "@crafting.tab_wait_anim" ],
        $offset: "$top_tab_anim_start"
      }
    ]}
/>)

inventoryScreen.addControl("tab_navigation_panel_layout/navigation_tabs/content", 
    <StackPanel modifications={[
        {
            operation: "insert_front",
            array_name: "controls",
            value: [
                {
                    "test_tab_panel": {
                        "type": "panel",
                        "size": [ 25, "100%" ],
                        "$is_left_most_tab": false,
                        "controls": [
                            {
                                "type": "image",
                                "texture": "textures/misc/Black",
                                "size": [ "100%", "100%" ], 
                            },
                            {
                                "test_tab_factory": {
                                    "type": "factory",
                                    "control_ids": {
                                        "test_tab": "@crafting.test_tab"
                                    }
                                }
                            }
                        ]
                    }
                }
            ]
        }
    ]}/>
)

createFile(JSON.stringify(inventoryScreen.toJson(), undefined, 4))