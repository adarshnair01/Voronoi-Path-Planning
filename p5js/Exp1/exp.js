// Require the dependency
var execSync = require("exec-sync");

// The traditional way
var exec = require('child_process').exec;
exec('cd ..', function(err, stdout, stderr) {
	// React to callback

	exec('ls', function(err2, stdout2, stderr2) {
		// More reacting

		// ... more nesting that isn't desired
	});
});
