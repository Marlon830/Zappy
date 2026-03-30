package org.zoatmc.core.game.object;

import org.bukkit.Location;
import org.bukkit.Particle;
import org.bukkit.World;
import org.joml.Vector3d;

public class ZParticle {

    private final Particle particle;
    private final Vector3d offset;
    private final Vector3d spread;
    private final int amount;
    private final int speed;
    private final boolean force;

    public ZParticle(Particle particle, Vector3d offset, Vector3d spread, int amount, int speed, boolean force) {
        this.particle = particle;
        this.offset = offset;
        this.spread = spread;
        this.amount = amount;
        this.speed = speed;
        this.force = force;
    }

    public ZParticle(Particle particle, Vector3d offset, Vector3d spread, int amount, int speed) {
        this(particle, offset, spread, amount, speed, false);
    }

    public ZParticle(Particle particle, Vector3d offset, Vector3d spread, int amount) {
        this(particle, offset, spread, amount, 1);
    }

    public ZParticle(Particle particle, Vector3d offset, Vector3d spread) {
        this(particle, offset, spread, 1);
    }

    public ZParticle(Particle particle, Vector3d offset) {
        this(particle, offset, new Vector3d());
    }

    public ZParticle(Particle particle) {
        this(particle, new Vector3d());
    }

    public void spawnParticle(Location location) {
        World world = location.getWorld();
        if (world == null)
            return;

        world.spawnParticle(particle, location.clone().add(offset.x, offset.y, offset.z), amount, spread.x, spread.y, spread.z, speed, null, force);
    }

}
