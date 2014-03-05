function SceneInfo() {
};

SceneInfo.prototype.initialize = function() {
	console.log("SceneInfo.initialize()");
};

SceneInfo.prototype.show = function() {
	History.pushState({scene: '#SceneInfo'}, "Info", "?st=info");
};