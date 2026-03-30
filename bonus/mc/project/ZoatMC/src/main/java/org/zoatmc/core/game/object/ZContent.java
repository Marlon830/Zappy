package org.zoatmc.core.game.object;

import org.bukkit.ChatColor;
import org.bukkit.Material;

import java.util.Arrays;

public class ZContent {

    protected int[] resources;

    public ZContent() {
        this.resources = new int[ResourceType.values().length];
        Arrays.fill(this.resources, 0);
    }

    public ZContent(int[] resources) {
        if (resources.length != ResourceType.values().length)
            throw new IllegalArgumentException("Invalid resources length");
        this.resources = resources;
    }

    public synchronized int[] getResourcesQuantities() {
        return this.resources;
    }

    public synchronized void setResourcesQuantities(int[] resources) {
        this.resources = resources;
    }

    public synchronized void setResourcesQuantities(ZContent content) {
        this.resources = content.resources;
    }

    public synchronized void setResourceQuantity(ResourceType type, int amount) {
        this.resources[type.ordinal()] = amount;
    }

    public synchronized int getResourceQuantity(ResourceType type) {
        return this.resources[type.ordinal()];
    }

    public void addResourceQuantity(ResourceType type, int amount) {
        this.resources[type.ordinal()] += amount;
    }

    public void removeResourceQuantity(ResourceType type, int amount) {
        this.resources[type.ordinal()] -= amount;
    }

    public enum ResourceType {
        FOOD(Material.CHICKEN, ChatColor.LIGHT_PURPLE),
        LINEMATE(Material.COAL, ChatColor.DARK_GRAY),
        DERAUMERE(Material.IRON_INGOT, ChatColor.WHITE),
        SIBUR(Material.GOLD_INGOT, ChatColor.GOLD),
        MENDIANE(Material.EMERALD, ChatColor.GREEN),
        PHIRAS(Material.DIAMOND, ChatColor.AQUA),
        THYSTAME(Material.NETHERITE_INGOT, ChatColor.DARK_PURPLE);

        private final Material material;
        private final ChatColor color;

        ResourceType(Material material, ChatColor color) {
            this.material = material;
            this.color = color;
        }

        public static ResourceType fromMaterial(Material type) {
            for (ResourceType resourceType : values()) {
                if (resourceType.getMaterial() == type)
                    return resourceType;
            }
            return null;
        }

        public String getName() {
            // Capitalize first letter only, the rest is lowercase
            return this.name().substring(0, 1) + this.name().substring(1).toLowerCase();
        }

        public Material getMaterial() {
            return this.material;
        }

        public ChatColor getColor() {
            return this.color;
        }

        public String getDisplayName() {
            return this.getColor() + this.getName();
        }
    }

}
