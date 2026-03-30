package org.zoatmc.core.command.sub;

import org.bukkit.command.Command;
import org.bukkit.command.CommandExecutor;
import org.bukkit.command.CommandSender;
import org.bukkit.entity.Player;
import org.jetbrains.annotations.NotNull;
import org.zoatmc.core.ZoatPlugin;
import org.zoatmc.core.command.ZoatFormatter;

public class SetupSubcommand implements CommandExecutor {
    @Override
    public boolean onCommand(@NotNull CommandSender sender, @NotNull Command command, @NotNull String alias, @NotNull String[] args) {
        if (!(sender instanceof Player player)) {
            sender.spigot().sendMessage(ZoatFormatter.error("You must be a player to use this command"));
            return true;
        } else if (args.length != 0)
            return false;

        ZoatPlugin zoat = ZoatPlugin.getInstance();
        if (!zoat.canSendResourcePack()) {
            player.spigot().sendMessage(
                ZoatFormatter.error("The resource server is not up, thus we cannot send you the resource pack. " +
                                    "If you are an admin, please check the server logs."));
            return true;
        }

        zoat.getResourceServer().transferResourcePack(player,
            "The Zoat resource pack improves your experience on the server through custom elements.");

        player.spigot().sendMessage(
            ZoatFormatter.info("We have sent you the request to use the resource pack. Please accept it and/or wait."));

        return true;
    }
}
