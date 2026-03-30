package org.zoatmc.core.command.sub;

import org.bukkit.command.Command;
import org.bukkit.command.CommandExecutor;
import org.bukkit.command.CommandSender;
import org.bukkit.command.TabCompleter;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;
import org.zoatmc.core.ZoatPlugin;
import org.zoatmc.core.command.ZoatFormatter;
import org.zoatmc.core.game.manager.ZGameManager;

import java.io.IOException;
import java.util.List;
import java.util.logging.Level;

public class DeleteSubcommand implements CommandExecutor, TabCompleter {
    @Override
    public boolean onCommand(@NotNull CommandSender sender, @NotNull Command command, @NotNull String alias, @NotNull String[] args) {
        if (args.length != 1)
            return false;

        String gameName = args[0];

        if (!ZGameManager.hasGame(gameName)) {
            sender.spigot().sendMessage(ZoatFormatter.error("Game '%s' does not exist", gameName));
            return true;
        }

        try {
            ZGameManager.removeGame(gameName);
            sender.spigot().sendMessage(ZoatFormatter.info("Game '%s' deleted successfully", gameName));
        } catch (IOException e) {
            sender.spigot().sendMessage(ZoatFormatter.error("Failed to delete game '%s': %s", gameName, e.getMessage()));
            ZoatPlugin.getInstance()
                      .getLogger()
                      .log(Level.FINE, "Failed to delete game '%s'".formatted(gameName), e);
        }

        return true;
    }

    @Nullable
    @Override
    public List<String> onTabComplete(@NotNull CommandSender sender, @NotNull Command command, @NotNull String label, @NotNull String[] args) {
        return ZGameManager.getGames().keySet().stream().toList();
    }
}