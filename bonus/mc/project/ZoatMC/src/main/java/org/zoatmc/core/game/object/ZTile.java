package org.zoatmc.core.game.object;

import org.bukkit.Location;
import org.bukkit.Material;
import org.bukkit.block.Block;
import org.bukkit.block.data.type.TurtleEgg;
import org.bukkit.entity.ItemDisplay;
import org.bukkit.util.Transformation;
import org.joml.Vector2i;
import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.util.DisplayGenerator;

import java.util.Arrays;
import java.util.Random;

public class ZTile extends ZContent {

    private final ItemDisplay[] displays;
    private final Location location;
    private final Vector2i pos;

    private int eggs = 0;

    public ZTile(ZGame game, Vector2i pos) {
        this.displays = new ItemDisplay[ZContent.ResourceType.values().length];
        this.location = game.getMapLocation().clone().add(pos.x * ZGame.TILE_SIZE, 0, pos.y * ZGame.TILE_SIZE);
        Arrays.fill(this.resources, 1);
        this.pos = pos;

        this.init();
    }

    public void init() {
        this.placeBlocks((pos.x + pos.y) % 2 == 0 ? Material.GRASS_BLOCK : Material.MOSS_BLOCK);
        this.initDisplays();
    }

    private void initDisplays() {
        Random random = new Random();

        for (ZContent.ResourceType type : ZContent.ResourceType.values()) {
            float x = random.nextFloat() * (ZGame.TILE_SIZE - 1) + 0.5f;
            float z = random.nextFloat() * (ZGame.TILE_SIZE - 1) + 0.5f;
            float y = random.nextFloat() * 0.01f;
            float angle = random.nextFloat() * 360;

            this.displays[type.ordinal()] = DisplayGenerator.generateItemDisplay(
                this.location.clone().add(x, y, z),
                type.getMaterial(),
                this.getResourceQuantity(type),
                angle
            );
        }
    }

    private void placeBlocks(Material material) {
        for (int x = 0; x < ZGame.TILE_SIZE; x++)
            for (int z = 0; z < ZGame.TILE_SIZE; z++)
                this.location.clone().add(x, -1, z).getBlock().setType(material);
    }

    public void updateDisplays() {
        for (ZContent.ResourceType type : ZContent.ResourceType.values()) {
            ItemDisplay display = this.displays[type.ordinal()];
            Transformation transformation = display.getTransformation();
            display.setTransformation(DisplayGenerator
                    .generateTransformation(90, transformation.getRightRotation().angle(), getResourceQuantity(type)));
        }
    }

    public void clearTile() {
        this.clearDisplays();
        this.placeBlocks(Material.AIR);

        this.eggs = 0;
        this.updateEggDisplays();
    }

    private void clearDisplays() {
        for (ItemDisplay display : displays)
            display.remove();
    }

    private void updateEggDisplays() {
        Block eggBlock = this.location.clone().add(ZGame.TILE_SIZE / 2.0, 0, ZGame.TILE_SIZE / 2.0).getBlock();

        if (this.eggs <= 0) {
            eggBlock.setType(Material.AIR);
            return;
        }

        if (eggBlock.getType() != Material.TURTLE_EGG)
            eggBlock.setType(Material.TURTLE_EGG);
        TurtleEgg egg = (TurtleEgg)eggBlock.getBlockData();
        egg.setEggs(Math.min(this.eggs, egg.getMaximumEggs()));
        eggBlock.setBlockData(egg);
    }

    public void addEgg() {
        this.eggs++;
        updateEggDisplays();
    }

    public void removeEgg() {
        this.eggs--;
        updateEggDisplays();
    }

    public Location getLocation() {
        return location;
    }
}
