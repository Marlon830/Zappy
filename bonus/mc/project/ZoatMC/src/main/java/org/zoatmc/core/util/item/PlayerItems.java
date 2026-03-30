package org.zoatmc.core.util.item;

import org.bukkit.Material;
import org.bukkit.inventory.ItemStack;
import org.bukkit.inventory.meta.ItemMeta;

public class PlayerItems {
    public static final ItemStack SPECTATE = new ItemStack(Material.PAPER);

    static {
        ItemMeta meta;

        meta = PlayerItems.SPECTATE.getItemMeta();
        meta.setDisplayName("§eSpectate");
        meta.setCustomModelData(1004);
        PlayerItems.SPECTATE.setItemMeta(meta);
    }
}
