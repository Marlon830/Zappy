package org.zoatmc.core.command.sub;

import org.bukkit.command.Command;
import org.bukkit.command.CommandExecutor;
import org.bukkit.command.CommandSender;
import org.bukkit.command.TabCompleter;
import org.bukkit.entity.Player;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;
import org.zoatmc.core.command.ZoatFormatter;
import org.zoatmc.core.game.manager.ZControllerManager;

import java.util.List;

public class LeaveSubcommand implements CommandExecutor, TabCompleter {
    @Override
    public boolean onCommand(@NotNull CommandSender sender, @NotNull Command command, @NotNull String label, @NotNull String[] args) {
        if (args.length != 0)
            return false;

        if (!(sender instanceof Player player)) {
            sender.spigot().sendMessage(ZoatFormatter.error("You must be a player to use this command."));
            return true;
        }

        if (!ZControllerManager.isController(player)) {
            sender.spigot().sendMessage(ZoatFormatter.error("You are not in control of a player."));
            return true;
        }

        ZControllerManager.getController(player).close();
        sender.spigot().sendMessage(ZoatFormatter.info("Disconnected from the game server."));

        return true;
    }

    @Nullable
    @Override
    public List<String> onTabComplete(@NotNull CommandSender sender, @NotNull Command command, @NotNull String label, @NotNull String[] args) {
        return null;
    }
}
