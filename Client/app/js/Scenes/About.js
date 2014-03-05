function SceneAbout() {

};

SceneAbout.prototype.initialize = function () {
	console.log("SceneAbout.initialize()");
};

SceneAbout.prototype.show = function() {
	History.pushState({scene: '#SceneAbout'}, "About", "?st=about");
};