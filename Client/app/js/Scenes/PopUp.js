function ScenePopUp() {

};

ScenePopUp.prototype.initialize = function () {
	console.log("ScenePopUp.initialize()");
	
	$("#PopUpCase").delegate("#ok", "click", function(event) {
		console.log("[button click] ok");
		scripts.switchScenes(sourceScene);
		switch (action) {
		case 'exit':
			sf.core.exit(false);
			break;
		default:
			break;
		}
		
		event.stopPropagation();
	});
};

ScenePopUp.prototype.show = function() {

};