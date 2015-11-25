var remote = require('electron').remote;

function connect() {
    var port = remote.getGlobal("neutron_port");
    return new NeutronConnection(port);
}

function NeutronConnection(port) {
    this.port = port;
}

function dispatch_callback(result, callback) {
    if (result.result_type == 'return') {
        callback(null, result.return_value);
    } else {
        callback('result indicated error');
    }
}

NeutronConnection.prototype.call = function call(member_path, args_order, args, callback) {
    // Create the request
    var req = {
        member_path: member_path,
        args_order: args_order,
        args: args
    }

    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function handler() {
        if (xhr.readyState == 4) {
            if (xhr.status != 200) {
                throw "neutron call failed";
            }
            var result = JSON.parse(xhr.responseText);
            dispatch_callback(result, callback);
        } else {
            console.log("xhr state: " + xhr.readyState);
        }
    };


    var url = "http://localhost:" + this.port + "/_neutron/invoke";
    console.log("neutron issuing xhr: " + url);
    xhr.open("POST", url, true);
    xhr.setRequestHeader('Content-Type', 'application/json');

    var body = JSON.stringify(req);
    console.log("neutron request: " + body);
    xhr.send(body);
}

window.neutron = connect();