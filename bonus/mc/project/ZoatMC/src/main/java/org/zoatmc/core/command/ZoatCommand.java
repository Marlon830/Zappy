package org.zoatmc.core.command;

import org.bukkit.command.Command;
import org.bukkit.command.CommandExecutor;
import org.bukkit.command.CommandSender;
import org.bukkit.command.TabCompleter;
import org.bukkit.util.StringUtil;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;
import org.zoatmc.core.util.ZCommandBuilder;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;

public class ZoatCommand implements CommandExecutor, TabCompleter {

    private static final HashMap<String, ZCommandBuilder> commands = new HashMap<>();

    @Override
    public boolean onCommand(@NotNull CommandSender sender, @NotNull Command command, @NotNull String label, @NotNull String @NotNull [] args) {
        if (args.length == 0) {
            sender.spigot().sendMessage(ZoatFormatter.error("Try /zoat help for a list of available sub-commands."));
            return true;
        }

        ZCommandBuilder commandBuilder = commands.get(args[0]);
        if (commandBuilder == null) {
            sender.spigot().sendMessage(ZoatFormatter.error("Unknown command '%s'.", args[0]));
            return true;
        }

        if (commandBuilder.getPermission() != null && !sender.hasPermission(commandBuilder.getPermission())) {
            sender.spigot().sendMessage(ZoatFormatter.error("You do not have permission to execute this command."));
            return true;
        }

        if (commandBuilder.getCommandExecutor() == null) {
            sender.spigot().sendMessage(ZoatFormatter.error("This command is not available."));
            return true;
        }

        if (!commandBuilder.getCommandExecutor().onCommand(sender, command, label, Arrays.copyOfRange(args, 1, args.length)))
            sender.spigot().sendMessage(ZoatFormatter.error("Usage: %s", commandBuilder.getUsage()));
        return true;
    }

    @Nullable
    @Override
    public List<String> onTabComplete(@NotNull CommandSender sender, @NotNull Command command, @NotNull String label, @NotNull String[] args) {
        List<String> completions = new ArrayList<>();
        if (args.length == 1) {
            List<String> allowedCommands = new ArrayList<>();
            for (ZCommandBuilder commandBuilder : commands.values()) {
                if (commandBuilder.getPermission() == null || sender.hasPermission(commandBuilder.getPermission()))
                    allowedCommands.add(commandBuilder.getName());
            }

            StringUtil.copyPartialMatches(args[0], allowedCommands, completions);
        } else if (args.length > 1) {
            ZCommandBuilder commandBuilder = commands.get(args[0]);
            if (commandBuilder != null && commandBuilder.getTabCompleter() != null && commandBuilder.getPermission() != null && sender.hasPermission(commandBuilder.getPermission()))
                return commandBuilder.getTabCompleter().onTabComplete(sender, command, label, Arrays.copyOfRange(args, 1, args.length));
        }
        return completions;
    }

    public static void registerCommand(ZCommandBuilder commandBuilder) {
        commands.put(commandBuilder.getName(), commandBuilder);
    }

    public static List<ZCommandBuilder> getCommands() {
        return new ArrayList<>(commands.values());
    }
}
