package org.zoatmc.core.command.sub;

import net.md_5.bungee.api.chat.BaseComponent;
import net.md_5.bungee.api.chat.ClickEvent;
import net.md_5.bungee.api.chat.ComponentBuilder;
import net.md_5.bungee.api.chat.HoverEvent;
import net.md_5.bungee.api.chat.hover.content.Text;
import org.bukkit.command.Command;
import org.bukkit.command.CommandExecutor;
import org.bukkit.command.CommandSender;
import org.jetbrains.annotations.NotNull;
import org.zoatmc.core.ZoatPlugin;
import org.zoatmc.core.command.ZoatCommand;
import org.zoatmc.core.command.ZoatFormatter;
import org.zoatmc.core.util.ZCommandBuilder;

import java.util.ArrayList;
import java.util.List;

public class HelpSubcommand implements CommandExecutor {
    private static final int HELP_PER_PAGE = 8;

    private static final String ORNAMENTS = "─".repeat(14);
    private static final String SPACER = " ".repeat(4);

    private static BaseComponent preTitle;

    static {
        ComponentBuilder builder = new ComponentBuilder();

        builder.append(HelpSubcommand.ORNAMENTS)
               .color(ZoatFormatter.COLOR_BASE)
               .append("  %s  ".formatted(ZoatPlugin.getInstance().getName()))
               .color(ZoatFormatter.COLOR_ACCENT)
               .append(HelpSubcommand.ORNAMENTS)
               .color(ZoatFormatter.COLOR_BASE);

        HelpSubcommand.preTitle = builder.build();
    }

    private static BaseComponent helpNextPage;
    private static BaseComponent helpPreviousPage;

    static {
        {
            ComponentBuilder builder = new ComponentBuilder();

            builder.append("Next page")
                    .color(ZoatFormatter.COLOR_ACCENT);

            HelpSubcommand.helpNextPage = builder.build();
        }

        {
            ComponentBuilder builder = new ComponentBuilder();

            builder.append("Previous page")
                    .color(ZoatFormatter.COLOR_ACCENT);

            HelpSubcommand.helpPreviousPage = builder.build();
        }
    }

    private static BaseComponent navigator(String alias, int pageNo, int pageCount)
    {
        ComponentBuilder builder = new ComponentBuilder();

        builder.append("<<")
               .color(ZoatFormatter.COLOR_BASE)
               .event(new HoverEvent(HoverEvent.Action.SHOW_TEXT, new Text(HelpSubcommand.helpPreviousPage)))
               .event(new ClickEvent(ClickEvent.Action.RUN_COMMAND, "/%s help %d".formatted(alias, pageNo - 1)))

               .append(" ".repeat(70))
               .event((HoverEvent) null)
               .event((ClickEvent) null)

               .append(">>")
               .color(ZoatFormatter.COLOR_BASE)
               .event(new HoverEvent(HoverEvent.Action.SHOW_TEXT, new Text(HelpSubcommand.helpNextPage)))
               .event(new ClickEvent(ClickEvent.Action.RUN_COMMAND, "/%s help %d".formatted(alias, pageNo + 1)));

        return builder.build();
    }

    private static BaseComponent postTitle(int pageNo, int pageCount)
    {
        ComponentBuilder builder = new ComponentBuilder();

        builder.append(HelpSubcommand.ORNAMENTS)
               .color(ZoatFormatter.COLOR_BASE)
               .append(" Page ")
               .color(ZoatFormatter.COLOR_NEUTRAL)
               .append(String.valueOf(pageNo))
               .color(ZoatFormatter.COLOR_ACCENT)
               .append("/")
               .color(ZoatFormatter.COLOR_BASE)
               .append(String.valueOf(pageCount))
               .color(ZoatFormatter.COLOR_ACCENT)
               .append(" ")
               .append(HelpSubcommand.ORNAMENTS)
               .color(ZoatFormatter.COLOR_BASE);

        return builder.build();
    }

    private static BaseComponent commandSuggestHoverText;

    static
    {
        ComponentBuilder builder = new ComponentBuilder();

        builder.append("Click to auto-complete this command in your chat box")
                .color(ZoatFormatter.COLOR_NEUTRAL);

        HelpSubcommand.commandSuggestHoverText = builder.build();
    }

    @Override
    public boolean onCommand(@NotNull CommandSender sender, @NotNull Command command, @NotNull String alias, @NotNull String[] args) {
        int page = 1;
        if (args.length > 0) {
            try {
                page = Integer.parseInt(args[0]);
            } catch (NumberFormatException _) {}
        }

        this.sendHelpMessage(alias, sender, page);
        return true;
    }

    private List<BaseComponent> getPlayerHelpMessages(String alias, CommandSender sender) {
        List<BaseComponent> messages = new ArrayList<>();

        for (ZCommandBuilder commandBuilder : ZoatCommand.getCommands()) {
            if (!commandBuilder.canExecute(sender))
                continue;

            ComponentBuilder componentBuilder = new ComponentBuilder();

            HoverEvent hoverEvent = new HoverEvent(HoverEvent.Action.SHOW_TEXT, new Text(HelpSubcommand.commandSuggestHoverText));
            ClickEvent clickEvent = new ClickEvent(ClickEvent.Action.SUGGEST_COMMAND, "/%s %s".formatted(alias, commandBuilder.getName()));

            componentBuilder
                .append(" » ")
                .color(ZoatFormatter.COLOR_BASE)
                .append(commandBuilder.getUsage())
                .color(ZoatFormatter.COLOR_ACCENT)
                .event(hoverEvent)
                .event(clickEvent)
                .append("\n" + HelpSubcommand.SPACER)
                .append(commandBuilder.getDescription().replace("\n", "\n" + HelpSubcommand.SPACER))
                .color(ZoatFormatter.COLOR_NEUTRAL)
                .event(hoverEvent)
                .event(clickEvent);

            messages.add(componentBuilder.build());
        }

        return messages;
    }

    private void sendHelpMessage(String alias, CommandSender sender, int pageNo) {
        List<BaseComponent> messages = this.getPlayerHelpMessages(alias, sender);
        int totalPagesCount = (int) Math.ceil(messages.size() / (double) HelpSubcommand.HELP_PER_PAGE);

        if (pageNo < 1 || pageNo > totalPagesCount) {
            sender.spigot().sendMessage(ZoatFormatter.error("Invalid page number (1-%s).", totalPagesCount));
            return;
        }

        sender.spigot().sendMessage(HelpSubcommand.preTitle);
        for (int i = 0; i < HELP_PER_PAGE; i++) {
            int index = (pageNo - 1) * HELP_PER_PAGE + i;
            if (index >= messages.size())
                break;
            sender.spigot().sendMessage(messages.get(index));
        }

        if (pageNo > 1)
            sender.spigot().sendMessage(HelpSubcommand.navigator(alias, pageNo, totalPagesCount));
        sender.spigot().sendMessage(HelpSubcommand.postTitle(pageNo, totalPagesCount));
    }
}
