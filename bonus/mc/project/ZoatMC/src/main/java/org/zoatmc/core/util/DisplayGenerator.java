package org.zoatmc.core.util;

import org.bukkit.Location;
import org.bukkit.Material;
import org.bukkit.entity.Display;
import org.bukkit.entity.ItemDisplay;
import org.bukkit.inventory.ItemStack;
import org.bukkit.util.Transformation;
import org.joml.AxisAngle4f;
import org.joml.Vector3f;

public class DisplayGenerator {

    public static ItemDisplay generateItemDisplay(Location location, Material material, int amount, Display.Billboard billboard, float left, float right) {
        if (location == null || location.getWorld() == null || material == null || amount < 0)
            return null;

        return location.getWorld().spawn(location, ItemDisplay.class, itemDisplay -> {
            itemDisplay.setItemStack(new ItemStack(material, amount));
            itemDisplay.setBillboard(billboard);
            itemDisplay.setTransformation(generateTransformation(left, right, amount));
        });
    }

    public static ItemDisplay generateItemDisplay(Location location, Material material, int amount, float angle) {
        return generateItemDisplay(location, material, amount, Display.Billboard.FIXED, 90, angle);
    }

    public static Transformation generateTransformation(float left, float right, int amount) {
        return new Transformation(
                new Vector3f(),
                new AxisAngle4f((float) Math.toRadians(left), 1, 0, 0),
                new Vector3f(amount > 0 ? 1 : 0, amount > 0 ? 1 : 0, amount),
                new AxisAngle4f((float) Math.toRadians(right), 0, 0, 1)
        );
    }

}
