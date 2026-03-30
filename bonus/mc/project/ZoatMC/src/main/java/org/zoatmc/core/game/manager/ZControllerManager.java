package org.zoatmc.core.game.manager;

import org.bukkit.entity.Player;
import org.zoatmc.core.game.object.ZPlayerController;

import java.util.HashMap;
import java.util.UUID;

public class ZControllerManager {

    private static final HashMap<UUID, ZPlayerController> controllers = new HashMap<>();

    public static void addController(ZPlayerController player) {
        controllers.put(player.getPlayer().getUniqueId(), player);
    }

    public static void removeController(ZPlayerController player) {
        if (player.isConnected())
            player.close();
        controllers.remove(player.getPlayer().getUniqueId());
    }

    public static void removeController(Player player) {
        ZPlayerController controller = controllers.get(player.getUniqueId());
        if (controller != null)
            removeController(controller);
    }

    public static ZPlayerController getController(Player player) {
        return controllers.get(player.getUniqueId());
    }

    public static boolean isController(Player player) {
        return ZControllerManager.controllers.containsKey(player.getUniqueId());
    }
}
