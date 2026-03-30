package org.zoatmc.core.game.object;

import org.bukkit.Bukkit;
import org.bukkit.Material;
import org.bukkit.entity.Player;
import org.bukkit.inventory.Inventory;
import org.bukkit.inventory.ItemStack;
import org.bukkit.inventory.meta.ItemMeta;
import org.jetbrains.annotations.Nullable;
import org.zoatmc.core.command.ZoatFormatter;
import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.protocol.player.ZClientCommandHandler;
import org.zoatmc.core.game.protocol.player.ZPlayerClient;
import org.zoatmc.core.util.item.ControllerItems;

import java.util.logging.Level;

public class ZPlayerController {

    private static Inventory actionInventory = null;

    private final Player player;
    private boolean connected;
    private final ZPlayerClient client;
    private final ZGame game;
    private final ZTeam team;
    private ZPlayer target = null;

    private ZContent.ResourceType actionContext = ZContent.ResourceType.FOOD;

    public ZPlayerController(ZGame game, ZTeam team, Player player) {
        this.game = game;
        this.team = team;
        this.connected = false;
        this.player = player;
        ZPlayerClient client = null;

        try {
            client = new ZPlayerClient(game.getHost(), game.getPort(), this);
        } catch (Exception e) {
            player.spigot().sendMessage(ZoatFormatter.error("Failed to connect to the remote game server."));
            Bukkit.getLogger().log(Level.FINE, "Failed to connect to the remote game server", e);
        }
        this.client = client;
    }

    public boolean isConnected() {
        return connected;
    }

    public void setConnected(boolean connected) {
        this.connected = connected;
    }

    @Nullable
    public ZClientCommandHandler getHandler() {
        if (client == null)
            return null;
        return client.getHandler();
    }

    public ZGame getGame() {
        return game;
    }

    public ZTeam getTeam() {
        return team;
    }

    public Player getPlayer() {
        return player;
    }

    public void onConnect() {
        player.spigot().sendMessage(ZoatFormatter.info("Connected to the game server."));

        Inventory inventory = player.getInventory();
        inventory.clear();

        inventory.setItem(0, ControllerItems.LEFT);
        inventory.setItem(1, ControllerItems.FORWARD);
        inventory.setItem(2, ControllerItems.RIGHT);
        inventory.setItem(3, ControllerItems.TAKE);
        inventory.setItem(4, ControllerItems.SET);
        inventory.setItem(5, ControllerItems.EJECT);
        inventory.setItem(6, ControllerItems.FORK);
        inventory.setItem(7, ControllerItems.INCANTATION);
        inventory.setItem(8, ControllerItems.INVENTORY);
    }

    public void close() {
        if (connected && client != null)
            client.close();
        connected = false;
    }

    public void setPlayer(ZPlayer player) {
        this.target = player;
    }

    public ZPlayer getTarget() {
        return target;
    }

    public ZContent.ResourceType getActionContext() {
        return actionContext;
    }

    public void setActionContext(ZContent.ResourceType actionContext) {
        this.actionContext = actionContext;
    }

    public void openActionInventory() {
        player.openInventory(getActionInventory());
    }

    public static Inventory getActionInventory() {
        if (actionInventory != null)
            return actionInventory;

        actionInventory = Bukkit.createInventory(null, 9, ZoatFormatter.COLOR_BASE.toString() + "Select a resource type");
        ItemStack empty = new ItemStack(Material.LIGHT_GRAY_STAINED_GLASS_PANE);
        ItemMeta meta = empty.getItemMeta();
        if (meta != null) {
            meta.setDisplayName(" ");
            empty.setItemMeta(meta);
        }

        actionInventory.setItem(0, empty);
        actionInventory.setItem(8, empty);
        for (int i = 1; i < 8; i++) {
            ZContent.ResourceType type = ZContent.ResourceType.values()[i - 1];
            actionInventory.setItem(i, createItemStack(type));
        }
        return actionInventory;
    }

    private static ItemStack createItemStack(ZContent.ResourceType type) {
        ItemStack item = new ItemStack(type.getMaterial());
        ItemMeta meta = item.getItemMeta();
        if (meta != null) {
            meta.setDisplayName(type.getColor() + type.name());
            item.setItemMeta(meta);
        }
        return item;
    }
}
