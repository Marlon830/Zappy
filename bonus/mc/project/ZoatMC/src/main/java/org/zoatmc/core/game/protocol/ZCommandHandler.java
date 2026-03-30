package org.zoatmc.core.game.protocol;

import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.protocol.watcher.impl.*;

import java.util.Arrays;
import java.util.HashMap;

public class ZCommandHandler {

    private static final HashMap<String, ZCommandExecutor> commands = new HashMap<>();
    private static boolean initialized = false;

    public static void registerCommand(String command, ZCommandExecutor executor) {
        commands.put(command, executor);
    }

    public static void registerCommands() {
        registerCommand("msz", new MapSizeCommand());
        registerCommand("bct", new MapTileCommand());
        registerCommand("tna", new TeamNameCommand());
        registerCommand("pnw", new PlayerJoinCommand());
        registerCommand("pdi", new PlayerDeathCommand());
        registerCommand("ppo", new PlayerPositionCommand());
        registerCommand("plv", new PlayerLevelCommand());
        registerCommand("pin", new PlayerInventoryCommand());
        registerCommand("enw", new EggSpawnCommand());
        registerCommand("ebo", new EggReplacedPerPlayerCommand());
        registerCommand("edi", new EggDeathCommand());
        registerCommand("pex", new PlayerExpulsionCommand());
        registerCommand("pbc", new PlayerBroadcastCommand());
        registerCommand("pic", new PlayerIncantationCommand());
        registerCommand("pie", new PlayerEndIncantationCommand());
        registerCommand("pfk", new PlayerForkCommand());
        registerCommand("pdr", new PlayerDropResourceCommand());
        registerCommand("pgt", new PlayerTakeResourceCommand());
        registerCommand("sgt", new TimeUnitCommand());
        registerCommand("sst", new TimeSetCommand());
        registerCommand("seg", new EndGameCommand());
    }

    public static void handleCommand(ZGame game, String command) {
        if (!initialized) {
            registerCommands();
            initialized = true;
        }

        String[] args = command.split(" ");
        ZCommandExecutor executor = ZCommandHandler.commands.get(args[0]);

        if (executor != null)
            executor.onCommand(game, args[0], Arrays.copyOfRange(args, 1, args.length));
    }
}
