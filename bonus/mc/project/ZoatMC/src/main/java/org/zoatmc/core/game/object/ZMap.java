package org.zoatmc.core.game.object;

import org.joml.Vector2i;
import org.zoatmc.core.game.ZGame;

import java.util.Arrays;
import java.util.function.Consumer;

public class ZMap {

    private final ZTile[] tiles;
    private final int width;
    private final int height;

    public ZMap(ZGame game, int width, int height) {
        this.width = width;
        this.height = height;
        this.tiles = new ZTile[width * height];
        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++)
                this.tiles[y * width + x] = new ZTile(game, new Vector2i(x, y));
    }

    public ZMap(ZGame game, Vector2i size) {
        this(game, size.x, size.y);
    }

    public synchronized ZTile getTile(int x, int y) {
        return this.tiles[y * width + x];
    }

    public synchronized int getWidth() {
        return this.width;
    }

    public synchronized int getHeight() {
        return this.height;
    }

    public synchronized void forEachTile(Consumer<ZTile> consumer) {
        Arrays.stream(this.tiles).forEach(consumer);
    }

    public void clear() {
        forEachTile(ZTile::clearTile);
    }

    public void init() {
        forEachTile(ZTile::init);
    }

}
