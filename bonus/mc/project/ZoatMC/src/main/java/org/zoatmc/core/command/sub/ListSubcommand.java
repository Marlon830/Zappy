package org.zoatmc.core.command.sub;

import org.bukkit.command.Command;
import org.bukkit.command.CommandExecutor;
import org.bukkit.command.CommandSender;
import org.jetbrains.annotations.NotNull;
import org.zoatmc.core.command.ZoatFormatter;
import org.zoatmc.core.game.manager.ZGameManager;

public class ListSubcommand implements CommandExecutor {
    @Override
    public boolean onCommand(@NotNull CommandSender sender, @NotNull Command command, @NotNull String alias, @NotNull String[] args) {
        if (args.length != 0)
            return false;

        sender.spigot().sendMessage(ZoatFormatter.info("There are %d games running right now", ZGameManager.getGames().size()));

        ZGameManager.getGames().forEach((name, game) ->
            sender.spigot().sendMessage(ZoatFormatter.state("Game '%s' at %s:%d", name, game.getHost(), game.getPort()))
        );

        return true;
    }
}
