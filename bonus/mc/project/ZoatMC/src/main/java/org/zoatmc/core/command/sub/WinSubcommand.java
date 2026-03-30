package org.zoatmc.core.command.sub;

import org.bukkit.command.Command;
import org.bukkit.command.CommandExecutor;
import org.bukkit.command.CommandSender;
import org.bukkit.command.TabCompleter;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;
import org.zoatmc.core.command.ZoatFormatter;
import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.event.watcher.ZGameEndEvent;
import org.zoatmc.core.game.manager.ZGameManager;
import org.zoatmc.core.game.object.ZTeam;

import java.util.List;

public class WinSubcommand implements CommandExecutor, TabCompleter {
    @Override
    public boolean onCommand(@NotNull CommandSender sender, @NotNull Command command, @NotNull String label, @NotNull String[] args) {
        if (args.length != 2)
            return false;

        ZGame game = ZGameManager.getGame(args[0]);
        if (game == null) {
            sender.spigot().sendMessage(ZoatFormatter.error("Game '%s' not found.", args[0]));
            return true;
        }

        ZTeam team = game.getTeam(args[1]);
        if (team == null) {
            sender.spigot().sendMessage(ZoatFormatter.error("Team '%s' not found.", args[1]));
            return false;
        }

        game.getEventBus().postEvent(new ZGameEndEvent(game, team));
        return true;
    }

    @Nullable
    @Override
    public List<String> onTabComplete(@NotNull CommandSender sender, @NotNull Command command, @NotNull String label, @NotNull String[] args) {
        if (args.length == 1)
            return ZGameManager.getGames().keySet().stream().toList();
        if (args.length == 2) {
            ZGame game = ZGameManager.getGame(args[0]);
            if (game == null)
                return List.of();
            return game.getTeams().keySet().stream().toList();
        }
        return null;
    }
}
