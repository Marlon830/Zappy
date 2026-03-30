package org.zoatmc.core.util.item;

import org.bukkit.Material;
import org.bukkit.entity.Item;
import org.bukkit.inventory.ItemStack;
import org.bukkit.inventory.meta.ItemMeta;

import java.lang.reflect.Field;
import java.lang.reflect.Modifier;
import java.util.ArrayList;
import java.util.List;

public class ControllerItems {
    public static final ItemStack FORWARD = new ItemStack(Material.PAPER);
    public static final ItemStack LEFT = new ItemStack(Material.PAPER);
    public static final ItemStack RIGHT = new ItemStack(Material.PAPER);
    public static final ItemStack FORK = new ItemStack(Material.PAPER);
    public static final ItemStack EJECT = new ItemStack(Material.PAPER);
    public static final ItemStack TAKE = new ItemStack(Material.PAPER);
    public static final ItemStack SET = new ItemStack(Material.PAPER);
    public static final ItemStack INCANTATION = new ItemStack(Material.EXPERIENCE_BOTTLE);
    public static final ItemStack INVENTORY = new ItemStack(Material.CHEST);

    static {
        ItemMeta meta;

        meta = ControllerItems.FORWARD.getItemMeta();
        meta.setDisplayName("§eForward");
        meta.setCustomModelData(1000);
        ControllerItems.FORWARD.setItemMeta(meta);

        meta = ControllerItems.LEFT.getItemMeta();
        meta.setDisplayName("§eLeft");
        meta.setCustomModelData(1002);
        ControllerItems.LEFT.setItemMeta(meta);

        meta = ControllerItems.RIGHT.getItemMeta();
        meta.setDisplayName("§eRight");
        meta.setCustomModelData(1003);
        ControllerItems.RIGHT.setItemMeta(meta);

        meta = ControllerItems.FORK.getItemMeta();
        meta.setDisplayName("§eFork");
        meta.setCustomModelData(1005);
        ControllerItems.FORK.setItemMeta(meta);

        meta = ControllerItems.EJECT.getItemMeta();
        meta.setDisplayName("§eEject");
        meta.setCustomModelData(1006);
        ControllerItems.EJECT.setItemMeta(meta);

        meta = ControllerItems.TAKE.getItemMeta();
        meta.setDisplayName("§eTake");
        meta.setCustomModelData(1007);
        ControllerItems.TAKE.setItemMeta(meta);

        meta = ControllerItems.SET.getItemMeta();
        meta.setDisplayName("§eSet");
        meta.setCustomModelData(1008);
        ControllerItems.SET.setItemMeta(meta);

        meta = ControllerItems.INCANTATION.getItemMeta();
        meta.setDisplayName("§eIncantation");
        ControllerItems.INCANTATION.setItemMeta(meta);

        meta = ControllerItems.INVENTORY.getItemMeta();
        meta.setDisplayName("§eInventory");
        ControllerItems.INVENTORY.setItemMeta(meta);
    }

    private static List<ItemStack> items = new ArrayList<>();

    static {
        try {
            for (Field field : ControllerItems.class.getDeclaredFields()) {
                if (!Modifier.isStatic(field.getModifiers()) ||
                    !field.getType().equals(ItemStack.class))
                    continue;

                items.add((ItemStack) field.get(null));
            }
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        }
    }

    public static boolean is(ItemStack item) {
        return ControllerItems.items.contains(item);
    }

    public static boolean is(Item item) {
        return ControllerItems.is(item.getItemStack());
    }
}
