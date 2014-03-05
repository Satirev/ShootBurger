function SceneOptions() {

};

SceneOptions.prototype.initialize = function () {

};

SceneOptions.prototype.show = function() {
	History.pushState({scene: '#SceneOptions'}, "Options", "?st=options");
};