var url = require('url');
var http = require('http');

var neutron_url = url.parse(process.env.NEUTRON_URL.trim());
if (neutron_url.protocol != "neutron+http:")
{
    throw "Unsupported protocol: " + neutron_url.protocol;
}

if (neutron_url.hostname != "localhost")
{ 
    throw "Unsupported host: " + neutron_url.hostname;
}

var server = require('http').createServer(function (request, response) {
});
server.listen(neutron_url.port);
console.log("Neutron Server Started at: " + url.format(neutron_url));