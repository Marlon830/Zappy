package org.zoatmc.core.listener;

import net.citizensnpcs.api.event.NPCRightClickEvent;
import net.citizensnpcs.api.npc.NPC;
import org.bukkit.Bukkit;
import org.bukkit.GameMode;
import org.bukkit.entity.HumanEntity;
import org.bukkit.entity.Player;
import org.bukkit.event.EventHandler;
import org.bukkit.event.Listener;
import org.bukkit.event.inventory.InventoryClickEvent;
import org.bukkit.event.inventory.InventoryMoveItemEvent;
import org.bukkit.event.inventory.InventoryType;
import org.bukkit.event.player.PlayerDropItemEvent;
import org.bukkit.event.player.PlayerJoinEvent;
import org.bukkit.event.player.PlayerQuitEvent;
import org.bukkit.event.player.PlayerToggleSneakEvent;
import org.bukkit.inventory.Inventory;
import org.zoatmc.core.ZoatPlugin;
import org.zoatmc.core.command.ZoatFormatter;
import org.zoatmc.core.game.manager.ZGameManager;
import org.zoatmc.core.game.object.ZPlayer;
import org.zoatmc.core.util.item.ControllerItems;
import org.zoatmc.core.util.item.PlayerItems;
import org.zoatmc.http.ResourceServer;

import java.util.Objects;

public class PlayerListener implements Listener {
    private HumanEntity entity;

    @EventHandler
    public void onPlayerJoin(PlayerJoinEvent event) {
        if (!ZoatPlugin.getInstance().canSendResourcePack())
            return;

        ResourceServer resourceServer = ZoatPlugin.getInstance().getResourceServer();

        resourceServer.transferResourcePack(event.getPlayer(),
            "The Zoat resource pack improves your experience on the server through custom elements.");
    }

    @EventHandler
    public void onPlayerQuit(PlayerQuitEvent event) {
        if (!ZoatPlugin.getInstance().canSendResourcePack())
            return;

        event.getPlayer().removeResourcePacks();
    }

    @EventHandler
    public void onInteractAtPlayer(NPCRightClickEvent event) {
        NPC npc = event.getNPC();
        ZPlayer player = ZGameManager.getPlayerByNPC(npc);

        if (player == null)
            return;

        event.getClicker().openInventory(player.getPlayerInventory());
    }

    @EventHandler
    public void onInventoryClick(InventoryClickEvent event) {
        Inventory inventory = event.getInventory();

        if (!ControllerItems.is(event.getCurrentItem()) &&
                (inventory.getType() != InventoryType.CHEST ||
                 inventory.getSize() != 9))
            return;

        event.setCancelled(true);

        if (Objects.equals(event.getCurrentItem(), PlayerItems.SPECTATE) &&
            inventory.getHolder() instanceof Player targetNpc &&
            event.getWhoClicked() instanceof Player player
        ) {
            player.setGameMode(GameMode.SPECTATOR);

            Bukkit.getScheduler().runTaskLater(ZoatPlugin.getInstance(), () -> {
                player.setSpectatorTarget(targetNpc);
                player.closeInventory();

                player.spigot().sendMessage(ZoatFormatter.info("You are now spectating '%s'.", targetNpc.getName()));
            }, 1L);
        }
    }

    @EventHandler
    public void onPlayerDropItem(PlayerDropItemEvent event) {
        event.setCancelled(ControllerItems.is(event.getItemDrop()));
    }

    @EventHandler
    public void onInventoryMoveItem(InventoryMoveItemEvent event) {
        event.setCancelled(ControllerItems.is(event.getItem()));
    }

    @EventHandler
    public void onPlayerSneak(PlayerToggleSneakEvent event) {
        Player player = event.getPlayer();

        if (player.getGameMode() == GameMode.SPECTATOR) {
            player.setGameMode(GameMode.CREATIVE);
            player.spigot().sendMessage(ZoatFormatter.info("You are no longer spectating."));
        }
    }
}
