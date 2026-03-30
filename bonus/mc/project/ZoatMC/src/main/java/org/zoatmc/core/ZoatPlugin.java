package org.zoatmc.core;

import net.citizensnpcs.api.CitizensAPI;
import net.citizensnpcs.api.npc.NPC;
import org.bukkit.command.PluginCommand;
import org.bukkit.plugin.PluginManager;
import org.bukkit.plugin.java.JavaPlugin;
import org.jetbrains.annotations.NotNull;
import org.zoatmc.core.command.ZoatCommand;
import org.zoatmc.core.command.sub.*;
import org.zoatmc.core.game.manager.ZGameManager;
import org.zoatmc.core.listener.ControllerListener;
import org.zoatmc.core.listener.EggListener;
import org.zoatmc.core.listener.NPCListener;
import org.zoatmc.core.listener.PlayerListener;
import org.zoatmc.core.util.ZCommandBuilder;
import org.zoatmc.http.ResourceServer;

import java.io.IOException;
import java.util.logging.Level;

public final class ZoatPlugin extends JavaPlugin {
    private static ZoatPlugin instance;

    private ResourceServer resourceServer = null;

    public static ZoatPlugin getInstance() {
        return ZoatPlugin.instance;
    }

    @Override
    public void onEnable() {
        ZoatPlugin.instance = this;
        PluginManager pm = this.getServer().getPluginManager();

        try {
            this.resourceServer = new ResourceServer();
            this.resourceServer.start();
            this.getLogger().info("Resource pack provider server started at " + this.resourceServer.getAddress());
        } catch (IOException e) {
            this.getLogger()
                .log(Level.SEVERE,
                    "Failed to start resource pack provider server -- the resource pack will not be sent to clients", e);
        }

        pm.registerEvents(new PlayerListener(), this);
        pm.registerEvents(new EggListener(), this);
        pm.registerEvents(new NPCListener(), this);
        pm.registerEvents(new ControllerListener(), this);

        this.registerCommands();
    }

    @Override
    public void onDisable() {
        if (this.resourceServer != null) {
            this.resourceServer.stop();
            this.getLogger()
                .log(Level.INFO, "Resource pack provider server stopped at " + this.resourceServer.getAddress());
        }

        ZGameManager.clear();

        CitizensAPI.getNPCRegistries()
            .forEach(registry -> registry.sorted()
                .forEach(NPC::destroy));
    }

    private void registerCommands() {
        ZoatCommand command = new ZoatCommand();

        PluginCommand cmd = this.getCommand("zoat");
        if (cmd != null) {
            cmd.setExecutor(command);
            cmd.setTabCompleter(command);
        }

        // Register commands
        ZoatCommand.registerCommand(
            new ZCommandBuilder("help")
                .setCommandExecutor(new HelpSubcommand())
                .setDescription("Display this help message.")
                .setUsage("/zoat help")
                .setPermission("zoat.meta.help"));

        ZoatCommand.registerCommand(
            new ZCommandBuilder("setup")
                .setCommandExecutor(new SetupSubcommand())
                .setDescription("Setup your client to use the integrated resource pack.")
                .setUsage("/zoat setup")
                .setPermission("zoat.meta.setup")
        );

        ZoatCommand.registerCommand(
            new ZCommandBuilder("create")
                .setCommandExecutor(new CreateSubcommand())
                .setDescription("Spawn a game window at your location with the specified IP address.")
                .setUsage("/zoat create <ip:port>")
                .setPermission("zoat.game.create"));

        ZoatCommand.registerCommand(
            new ZCommandBuilder("delete")
                .setCommandExecutor(new DeleteSubcommand())
                .setTabCompleter(new DeleteSubcommand())
                .setDescription("Delete the specified game window from the world that it has been created on.")
                .setUsage("/zoat delete <name>")
                .setPermission("zoat.game.delete")
        );

        ZoatCommand.registerCommand(
            new ZCommandBuilder("list")
                .setCommandExecutor(new ListSubcommand())
                .setDescription("List the currently active games on the server.")
                .setUsage("/zoat list")
                .setPermission("zoat.game.list")
        );

        ZoatCommand.registerCommand(
            new ZCommandBuilder("join")
                .setCommandExecutor(new JoinSubcommand())
                .setTabCompleter(new JoinSubcommand())
                .setDescription("Join the specified game and team.")
                .setUsage("/zoat join <game> <team>")
                .setPermission("zoat.game.join")
        );

        ZoatCommand.registerCommand(
            new ZCommandBuilder("leave")
                .setCommandExecutor(new LeaveSubcommand())
                .setTabCompleter(new LeaveSubcommand())
                .setDescription("Leave the current game and team.")
                .setUsage("/zoat leave")
                .setPermission("zoat.game.leave")
        );

        ZoatCommand.registerCommand(
            new ZCommandBuilder("win")
                .setCommandExecutor(new WinSubcommand())
                .setTabCompleter(new WinSubcommand())
                .setDescription("Win the specified team in the specified game.")
                .setUsage("/zoat win <game> <team>")
                .setPermission("zoat.game.win")
        );
    }

    public boolean canSendResourcePack() {
        return this.resourceServer != null;
    }

    public @NotNull ResourceServer getResourceServer() {
        assert this.resourceServer != null;
        return this.resourceServer;
    }
}
