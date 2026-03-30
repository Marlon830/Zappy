package org.zoatmc.core.listener;

import org.bukkit.Material;
import org.bukkit.block.Block;
import org.bukkit.event.EventHandler;
import org.bukkit.event.Listener;
import org.bukkit.event.block.Action;
import org.bukkit.event.block.BlockFadeEvent;
import org.bukkit.event.player.PlayerInteractEvent;

public class EggListener implements Listener {

    @EventHandler
    public void onTurtleEggBreak(PlayerInteractEvent event) {
        Action action = event.getAction();
        Block block = event.getClickedBlock();

        if (action != Action.PHYSICAL || block == null || block.getType() != Material.TURTLE_EGG)
            return;

        event.setCancelled(true);
    }

    @EventHandler
    public void onTurtleEggHatch(BlockFadeEvent event) {
        Block block = event.getBlock();

        if (block.getType() != Material.TURTLE_EGG)
            return;

        event.setCancelled(true);
    }

}
