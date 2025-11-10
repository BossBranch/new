import { GetRef, Image, Label, PanelProps, UiFile, createFile, createMinecraftElement } from "Regolith-Generators";

const startScreen = new UiFile("start");
const BaseVersion = GetRef<PanelProps>("start", "version");

interface VersionLabelProps extends PanelProps {
    text_binding: string;
}

function VersionLabel(props: VersionLabelProps) {
    return (
        <Label 
            color="$main_header_text_color" 
            text={props.text_binding} 
            size={["default", 10]} 
            max_size={["100%", "100%"]} 
            anchors="top_right"
            layer={2}
            bindings={[
                {
                    binding_name: props.text_binding,
                }
            ]}
        >
            <Image texture="textures/ui/Black" anchors="center" alpha={0.6} layer={-1} size={["100% + 2px", "100% + 2px"]} />
        </Label>
    );
}

startScreen.addControl("version", 
    <BaseVersion>
        <VersionLabel text_binding="#version" offset={[0, -24]} />
        <VersionLabel text_binding="#amethyst_version" offset={[0, -12]} />
        <VersionLabel text_binding="#mods_loaded" offset={[0, 0]} />
    </BaseVersion>
);

createFile(JSON.stringify(startScreen.toJson(), undefined, 4))