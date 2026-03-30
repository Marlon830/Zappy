package org.zoatmc.core.listener;

import org.bukkit.entity.Player;
import org.bukkit.event.EventHandler;
import org.bukkit.event.Listener;
import org.bukkit.event.block.Action;
import org.bukkit.event.inventory.InventoryClickEvent;
import org.bukkit.event.player.PlayerInteractEvent;
import org.bukkit.inventory.InventoryView;
import org.bukkit.inventory.ItemStack;
import org.zoatmc.core.command.ZoatFormatter;
import org.zoatmc.core.game.manager.ZControllerManager;
import org.zoatmc.core.game.object.ZContent;
import org.zoatmc.core.game.object.ZPlayerController;
import org.zoatmc.core.game.protocol.player.ZClientCommandHandler;
import org.zoatmc.core.util.item.ControllerItems;

import java.util.Objects;

public class ControllerListener implements Listener {

    @EventHandler
    public void onControllerEvent(PlayerInteractEvent event) {
        Player player = event.getPlayer();
        ItemStack item = event.getItem();

        if (item == null || item.getItemMeta() == null || !item.getItemMeta().hasDisplayName())
            return;

        ZPlayerController controller = ZControllerManager.getController(player);
        if (controller == null || !controller.isConnected())
            return;

        ZClientCommandHandler handler = controller.getHandler();
        if (handler == null)
            return;

        Action action = event.getAction();

        if (item.equals(ControllerItems.FORWARD))
            handler.forward();
        else if (item.equals(ControllerItems.LEFT))
            handler.left();
        else if (item.equals(ControllerItems.RIGHT))
            handler.right();
        else if (item.equals(ControllerItems.FORK))
            handler.fork();
        else if (item.equals(ControllerItems.EJECT))
            handler.eject();
        else if (item.equals(ControllerItems.TAKE)) {
            if (isLeftClick(action))
                handler.take(controller.getActionContext());
            else if (isRightClick(action))
                controller.openActionInventory();
        } else if (item.equals(ControllerItems.SET)) {
            if (isLeftClick(action))
                handler.set(controller.getActionContext());
            else if (isRightClick(action))
                controller.openActionInventory();
        } else if (item.equals(ControllerItems.INCANTATION))
            handler.incantation();
        else if (item.getItemMeta().getDisplayName().equals(Objects.requireNonNull(ControllerItems.INVENTORY.getItemMeta()).getDisplayName()))
            player.openInventory(controller.getTarget().getPlayerInventory());
        else
            return;

        event.setCancelled(true);
    }

    private boolean isLeftClick(Action action) {
        return action == Action.LEFT_CLICK_AIR || action == Action.LEFT_CLICK_BLOCK;
    }

    private boolean isRightClick(Action action) {
        return action == Action.RIGHT_CLICK_AIR || action == Action.RIGHT_CLICK_BLOCK;
    }

    @EventHandler
    public void inventoryClick(InventoryClickEvent event) {
        if (!(event.getWhoClicked() instanceof Player player))
            return;

        ZPlayerController controller = ZControllerManager.getController(player);
        if (controller == null || !controller.isConnected())
            return;

        InventoryView view = event.getView();

        if (view.getTitle().equals(ZoatFormatter.COLOR_BASE.toString() + "Select a resource type")) {
            ItemStack item = event.getCurrentItem();
            if (item != null) {
                ZContent.ResourceType type = ZContent.ResourceType.fromMaterial(item.getType());
                if (type != null) {
                    controller.setActionContext(type);
                    player.closeInventory();
                    player.spigot().sendMessage(ZoatFormatter.info("Selected %s", type.getColor() + type.name()));
                }
            }
        }

        event.setCancelled(true);
    }

}
