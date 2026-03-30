package org.zoatmc.core.game.object;

import org.joml.Vector2i;
import org.zoatmc.core.game.ZGame;

public class ZEgg {

    private final ZGame game;
    private final int id;
    private int x;
    private int y;

    public ZEgg(ZGame game, int id, int x, int y) {
        this.game = game;
        this.id = id;
        this.x = x;
        this.y = y;
    }

    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }

    public ZGame getGame() {
        return game;
    }

    public int getId() {
        return id;
    }

    public void setPosition(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public void setPosition(Vector2i position) {
        setPosition(position.x, position.y);
    }
}
