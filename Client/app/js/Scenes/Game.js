function SceneGame() {

};

SceneGame.prototype.initialize = function () {

};

SceneGame.prototype.show = function() {
	History.pushState({scene: '#SceneGame'}, "Game", "?st=game");
};