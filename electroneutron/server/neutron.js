var spawn = require('child_process').spawn;

module.exports = {};

module.exports.start = function start(app_base, server_command) {
    // TODO: allocate a port
    var port = 9090;
    
    // Split the server_command into args
    var splat = server_command.split(" ");
    var name = splat[0];
    var args = splat.slice(1, splat.length);
    
    // Set up environment
    var env = {};
    for (var key in Object.keys(process.env)) {
        env[key] = process.env[key];
    }
    env["NEUTRON_PORT"] = port;
    
    console.log("appbase: " + app_base);
    console.log("starting neutron server: " + server_command);
    var child = spawn(name, args, {
        cwd: app_base,
        env: env
    });
    child.stdout.on('data', function (data) {
        console.log(data.toString());
    });
    
    child.stderr.on('data', function (data) {
        console.log(data.toString());
    });
    console.log("started neutron server: " + child.pid);
    
    return new NeutronConnection(child, port);
};

function NeutronConnection(child, port) {
    this.child = child;
    this.port = port;
}
