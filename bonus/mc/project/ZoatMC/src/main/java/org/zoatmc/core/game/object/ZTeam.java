package org.zoatmc.core.game.object;

import net.md_5.bungee.api.ChatColor;
import org.bukkit.Color;
import org.bukkit.Material;
import org.bukkit.inventory.ItemStack;
import org.bukkit.inventory.meta.LeatherArmorMeta;

public class ZTeam {

    private final String name;
    private final Color color;

    public ZTeam(String name, Color color) {
        this.name = name;
        this.color = color;
    }

    public String getName() {
        return name;
    }

    public Color getColor() {
        return color;
    }

    public ItemStack getChestplate() {
        ItemStack chestplate = new ItemStack(Material.LEATHER_CHESTPLATE);
        LeatherArmorMeta meta = (LeatherArmorMeta) chestplate.getItemMeta();

        if (meta == null)
            return chestplate;

        meta.setColor(color);
        chestplate.setItemMeta(meta);

        return chestplate;
    }

    public ChatColor getChatColor() {
        return ChatColor.of(String.format("#%02x%02x%02x", color.getRed(), color.getGreen(), color.getBlue()));
    }
}
