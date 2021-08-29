import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0
import "." // QTBUG-34418, singletons require explicit import to load qmldir file

Window {
	signal signalUIParameterChaged(string name, variant value)
	signal signalUIAction(string name, variant value)
    signal signalUIMessageAnswer(string button);

    FontLoader{ id: fontRoboto; source: "/fonts/Roboto-Bold.ttf" }

	visible: true
	id: root
    x:0
    y:0
    width: 1024
    height: 600
	title: qsTr("AuroraCS") + cppLinguist.emptyString

	function applyValue(aName, aValue, aData)
	{
		if ("function" == typeof aData) // data contains a delegate function
		{
			aData(aValue); // call the delegate on the new value
		} 
		switch(aName)
		{
			default: console.log("Unhandled case in applyValue: [",aName,"] [",aValue,"]"); return;
		}

		uiParameterChanged(aName,aValue,aData);
	}

    function showMessage( aDataMap, aButtonsList )
    {
        if(!message.visible)
        {
            message.visible = true;
            message.setData(aDataMap, aButtonsList);
            message.currentMenu = currentMenu;
        }
    }

    function hideMessage( )
    {
        if(message.visible)
        {
            currentMenu = message.currentMenu;
            message.visible = false;
        }
    }

    function clickedMessage( aButton )
    {
        signalUIMessageAnswer(aButton);
        hideMessage();
    }

	function goTo(menuName)
	{
		currentMenu = menuName
	}

	function goToInput(aName,aValue,aKeyboardType,aCaption,aParentMenu,aData)
	{
		menuInput.goToInput(aName,aValue,aKeyboardType,aCaption,aParentMenu,aData)
	}

	function goToSelect(aName,aValue,aCaption,aParentMenu,aData)
	{
		menuSelect.goToSelect(aName,aValue,aCaption,aParentMenu,aData)
	}

	function uiParameterChanged(aName,aValue,aData)
	{
		console.log("UIParameterChanged: [",aName,"] [",aValue,"] [",aData,"]")
		signalUIParameterChaged(aName,aValue)
	}

	function uiAction(aName,aValue)
	{
		console.log("UIAction: [",aName,"] [",aValue,"]")
		signalUIAction(aName,aValue)
	}

	Component.onCompleted:
	{
		//showMessage(2,"Test UI message");
		//clearLayersList()
		//clearWiFiList()
		//clearSettingsList()
		//settingsConnectedWiFiCaption = "Caption 4"
        //cppLinguist.setCurrentLanguage("German")
	}

	Rectangle{
		anchors.fill: parent
		color: "#ff0000"
		Component.onCompleted:
		{
            message.signalClicked.connect(root.clickedMessage);
            message.signalUIAction.connect(root.uiAction);
			menuInput.signalApplyValue.connect(root.applyValue);
			menuSelect.signalApplyValue.connect(root.applyValue);
			for(var i = 0; i < children.length; ++i)
			{
				if(children[i].objectName === "MENU")
				{
					//console.log(children[i].name);
					children[i].signalShowMessage.connect(root.showMessage);
					children[i].signalGoToSelect.connect(root.goToSelect);
					children[i].signalGoToInput.connect(root.goToInput);
					children[i].signalGoTo.connect(root.goTo);
					children[i].signalUIAction.connect(root.uiAction);
					children[i].signalUIParameterChaged.connect(root.uiParameterChanged);
				}
			}
		}

		children: [
			TMenuInput				{ id: menuInput; visible: currentMenu === name },
			TMenuSelect				{ id: menuSelect; visible: currentMenu === name },
            TMessageExt 			{ id: message; visible: false },
            TMenuStart				{ id: menuStart; visible: currentMenu === name; materialName: settingsMaterialName; materialVolume: settingsMaterialVolume; materialVolumePrs: root.settingsMaterialVolumePrs; onVisibleChanged:{if(visible)cppUILogic.refreshData("material");} },
			TMenuEthernet			{ id: menuEthernet; visible: currentMenu === name },
			TMenuSettings			{ id: menuSettings; visible: currentMenu === name },
			TMenuWiFi				{ id: menuWiFi; visible: currentMenu === name },
			TMenuJobSettings		{ id: menuJobSettings; visible: currentMenu === name },
			TMenuMaterialInfo		{ id: menuMaterialInfo; visible: currentMenu === name },
			TMenuMoveCalibration	{ id: menuMoveCalibration; visible: currentMenu === name },
			TMenuHomeCalibration	{ id: menuHomeCalibration; visible: currentMenu === name },
			TMenuMotionCalibration	{ id: menuMotionCalibration; visible: currentMenu === name },
			TMenuTilting			{ id: menuTilting; visible: currentMenu === name },
			TMenuMove				{ id: menuMove; visible: currentMenu === name  },
			TMenuMachineInfo		{ id: menuMachineInfo; visible: currentMenu === name },
			TMenuService			{ id: menuService; visible: currentMenu === name },
			TMenuPower				{ id: menuPower; visible: currentMenu === name  },
            TMenuVNC				{ id: menuVNC; visible: currentMenu === name  },
            TMenuLogs				{ id: menuLogs; visible: currentMenu === name  },
            TMenuJobs				{ id: menuJobs; visible: currentMenu === name },
            TMenuJobProccessing		{
                id: menuJobProcessing
                visible: currentMenu === name
                status: menuJobs.curStatus
                material: menuJobs.materialName
                voxelDepth: menuJobs.curVoxelDepth
                layers: menuJobs.curNumOfLayers
                currentSpeed: menuJobs.curSpeed
                averageSpeed: menuJobs.averageSpeed
                indicatorMinutes: menuJobs.remainigTimeM
                indicatorSeconds: menuJobs.remainigTimeS
                currentJobName: menuJobs.currentJobName
            },
			TMenuLayers				{ id: menuLayers; visible: currentMenu === name },
			TMenuMachineSettings	{ id: menuMachineSettings; visible: currentMenu === name },
			TMenuUpdate				{ id: menuUpdate; visible: currentMenu === name },
            TMenuSensors			{ id: menuSensors; visible: currentMenu === name },
            TMenuCuringTest			{ id: menuCuringTest; visible: currentMenu === name },
            TMenuGreyscale			{ id: menuGreyscale; visible: currentMenu === name;spotsPerX: settingsSpotsPerX; spotsPerY: settingsSpotsPerY; spotsRadius: settingsSpotsRadius; },
            TMenuImage              { id: menuImage; visible: currentMenu === name },
            TMenuInformation        { id: menuInformation; visible: currentMenu === name },
            TMenuLanguage           { id: menulanguage; visible: currentMenu === name },
            TMenuMaskGeneration		{ id: menuMaskGeneration; visible: currentMenu === name; },
            TMenuProjectionPower	{ id: menuProjectionPower; visible: currentMenu === name },
            TMenuDLPTable           { id: menuDLPTable; visible: currentMenu === name },
            TMenuDLPTableGeneration { id: menuDLPTableGeneration; visible: currentMenu === name; maxSpotsCount: menuDLPTable.maxSpotsCount; dutyCycle: settingsDutyCycleValue}
		]
	}

    Text{
            id:waterMark
            visible: cppUIAssistant.isDebugVersion()
            anchors.centerIn: parent
            text: "For internal use"
            color: "#5FFFFFFF"
            rotation: -30
            font: Qt.font({ family: "Roboto", bold: true, pixelSize: 120 });
        }
}
