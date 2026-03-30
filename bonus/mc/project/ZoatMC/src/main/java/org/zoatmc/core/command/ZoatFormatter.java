package org.zoatmc.core.command;

import net.md_5.bungee.api.ChatColor;
import net.md_5.bungee.api.chat.BaseComponent;
import net.md_5.bungee.api.chat.ComponentBuilder;

public class ZoatFormatter {
    public static final ChatColor COLOR_BASE = ChatColor.of("#99271a");
    public static final ChatColor COLOR_ACCENT = ChatColor.of("#eb4634");
    public static final ChatColor COLOR_NEUTRAL = ChatColor.of("#c9c2c1");

    protected static BaseComponent stateIcon = null;
    protected static BaseComponent infoIcon = null;
    protected static BaseComponent warningIcon = null;
    protected static BaseComponent errorIcon = null;

    protected static BaseComponent core = null;

    static {
        {
            ComponentBuilder builder = new ComponentBuilder();

            builder.append("  ")
                   .color(ZoatFormatter.COLOR_NEUTRAL);

            ZoatFormatter.stateIcon = builder.build();
        }

        {
            ComponentBuilder builder = new ComponentBuilder();

            builder.append("🛈")
                   .color(ZoatFormatter.COLOR_NEUTRAL);

            ZoatFormatter.infoIcon = builder.build();
        }

        {
            ComponentBuilder builder = new ComponentBuilder();

            builder.append("⚠")
                   .color(ChatColor.of("#ffa200"));

            ZoatFormatter.warningIcon = builder.build();
        }

        {
            ComponentBuilder builder = new ComponentBuilder();

            builder.append("⮾")
                   .color(ChatColor.of("#fc0324"));

            ZoatFormatter.errorIcon = builder.build();
        }

        {
            ComponentBuilder builder = new ComponentBuilder();

            builder.append(" ")
                   .append("ZoatMC")
                   .color(ZoatFormatter.COLOR_ACCENT)
                   .append(" » ")
                   .color(ZoatFormatter.COLOR_BASE);

            ZoatFormatter.core = builder.build();
        }
    }

    public static BaseComponent format(BaseComponent icon, String message, Object... args) {
        ComponentBuilder builder = new ComponentBuilder();

        builder.append(icon)
               .append(ZoatFormatter.core)
               .color(ZoatFormatter.COLOR_NEUTRAL)
               .append(message.formatted(args));

        return builder.build();
    }

    public static BaseComponent state(String message, Object... args) {
        return ZoatFormatter.format(ZoatFormatter.stateIcon, message, args);
    }

    public static BaseComponent info(String message, Object... args) {
        return ZoatFormatter.format(ZoatFormatter.infoIcon, message, args);
    }

    public static BaseComponent warning(String message, Object... args) {
        return ZoatFormatter.format(ZoatFormatter.warningIcon, message, args);
    }

    public static BaseComponent error(String message, Object... args) {
        return ZoatFormatter.format(ZoatFormatter.errorIcon, message, args);
    }
}
