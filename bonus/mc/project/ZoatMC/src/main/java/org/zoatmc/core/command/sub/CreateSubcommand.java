package org.zoatmc.core.command.sub;

import org.bukkit.Location;
import org.bukkit.command.Command;
import org.bukkit.command.CommandExecutor;
import org.bukkit.command.CommandSender;
import org.bukkit.entity.Player;
import org.jetbrains.annotations.NotNull;
import org.zoatmc.core.ZoatPlugin;
import org.zoatmc.core.command.ZoatFormatter;
import org.zoatmc.core.game.ZGame;

import java.io.IOException;
import java.util.logging.Level;

public class CreateSubcommand implements CommandExecutor {
    @Override
    public boolean onCommand(@NotNull CommandSender sender, @NotNull Command command, @NotNull String alias, @NotNull String[] args) {
        if (!(sender instanceof Player player)) {
            sender.spigot().sendMessage(ZoatFormatter.error("You must be a player to use this command"));
            return true;
        }

        if (args.length != 1)
            return false;

        String[] split = args[0].split(":");

        if (split.length != 2)
            return false;
        String host = split[0];
        int port;

        try {
            port = Integer.parseInt(split[1]);
        } catch (NumberFormatException e) {
            sender.spigot().sendMessage(ZoatFormatter.error("Invalid port number '%s'", split[1]));
            return true;
        }

        Location gameLocation = player.getLocation().getBlock().getLocation();

        ZGame game;
        try {
            game = new ZGame(gameLocation, host, port);
        } catch (IOException e) {
            ZoatPlugin.getInstance()
                      .getLogger()
                      .log(Level.SEVERE, "Failed to create game from '%s:%d'".formatted(host, port), e);

            sender.spigot().sendMessage(ZoatFormatter.error("Failed to create game from '%s'", host, port));

            return true;
        }

        sender.spigot().sendMessage(ZoatFormatter.info("Game created as '%s'", game.getName()));

        return true;
    }
}
