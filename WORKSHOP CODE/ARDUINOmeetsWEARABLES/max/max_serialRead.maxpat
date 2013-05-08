{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 629.0, 64.0, 640.0, 480.0 ],
		"bglocked" : 0,
		"defrect" : [ 629.0, 64.0, 640.0, 480.0 ],
		"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
		"openinpresentation" : 0,
		"default_fontsize" : 9.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 0,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 0,
		"toolbarvisible" : 1,
		"boxanimatetime" : 200,
		"imprint" : 0,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "number",
					"fontsize" : 9.0,
					"presentation_rect" : [ 301.0, 393.0, 0.0, 0.0 ],
					"patching_rect" : [ 301.0, 393.0, 50.0, 17.0 ],
					"numinlets" : 1,
					"fontname" : "Arial",
					"numoutlets" : 2,
					"id" : "obj-17",
					"outlettype" : [ "int", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"fontsize" : 9.0,
					"presentation_rect" : [ 379.0, 350.0, 0.0, 0.0 ],
					"patching_rect" : [ 247.0, 392.0, 50.0, 17.0 ],
					"numinlets" : 1,
					"fontname" : "Arial",
					"numoutlets" : 2,
					"id" : "obj-15",
					"outlettype" : [ "int", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"fontsize" : 9.0,
					"presentation_rect" : [ 251.0, 349.0, 0.0, 0.0 ],
					"patching_rect" : [ 194.0, 392.0, 50.0, 17.0 ],
					"numinlets" : 1,
					"fontname" : "Arial",
					"numoutlets" : 2,
					"id" : "obj-13",
					"outlettype" : [ "int", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "number",
					"fontsize" : 9.0,
					"patching_rect" : [ 137.0, 392.0, 50.0, 17.0 ],
					"numinlets" : 1,
					"fontname" : "Arial",
					"numoutlets" : 2,
					"id" : "obj-11",
					"outlettype" : [ "int", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "unpack 0 0 0 0 0 0 0 0 0",
					"fontsize" : 9.0,
					"patching_rect" : [ 166.0, 295.0, 127.0, 17.0 ],
					"numinlets" : 1,
					"fontname" : "Arial",
					"numoutlets" : 9,
					"id" : "obj-5",
					"outlettype" : [ "int", "int", "int", "int", "int", "int", "int", "int", "int" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "fromsymbol `separator,",
					"fontsize" : 9.0,
					"patching_rect" : [ 166.0, 269.0, 103.0, 17.0 ],
					"numinlets" : 1,
					"fontname" : "Arial",
					"numoutlets" : 1,
					"id" : "obj-1",
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "itoa",
					"fontsize" : 9.0,
					"patching_rect" : [ 166.0, 246.0, 40.0, 17.0 ],
					"numinlets" : 3,
					"fontname" : "Arial",
					"numoutlets" : 1,
					"id" : "obj-8",
					"outlettype" : [ "int" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "bangs when there is data",
					"linecount" : 4,
					"fontsize" : 9.0,
					"patching_rect" : [ 77.0, 121.0, 49.0, 48.0 ],
					"numinlets" : 1,
					"fontname" : "Arial",
					"numoutlets" : 0,
					"id" : "obj-314"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "click to make the toggle swithc on",
					"fontsize" : 9.0,
					"patching_rect" : [ 166.0, 56.0, 148.0, 17.0 ],
					"numinlets" : 1,
					"fontname" : "Arial",
					"numoutlets" : 0,
					"id" : "obj-312"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "20 is the breaker bite on arduino. (that is how I programed it on this example) ",
					"linecount" : 5,
					"fontsize" : 9.0,
					"patching_rect" : [ 74.0, 180.0, 81.0, 58.0 ],
					"numinlets" : 1,
					"fontname" : "Arial",
					"numoutlets" : 0,
					"id" : "obj-310"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "choose your serial port and baud rate. baudrate should match with what you have programed on arudino. Do not set baudrate faster than 9600 on lilypad",
					"linecount" : 3,
					"fontsize" : 9.0,
					"patching_rect" : [ 281.0, 180.0, 232.0, 38.0 ],
					"numinlets" : 1,
					"fontname" : "Arial",
					"numoutlets" : 0,
					"id" : "obj-308"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Arduino is programed to send serial when available. that is why you have to send \"99\" (or anything) to start communication. If you do not have \"serial available\" on arduino, it crashes max. you have to send \"99\" again when arduino/lilypad is reset.",
					"linecount" : 7,
					"fontsize" : 9.0,
					"patching_rect" : [ 331.0, 47.0, 154.0, 79.0 ],
					"numinlets" : 1,
					"fontname" : "Arial",
					"numoutlets" : 0,
					"id" : "obj-304"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "umenu",
					"fontsize" : 10.0,
					"labelclick" : 1,
					"types" : [  ],
					"patching_rect" : [ 374.0, 157.0, 100.0, 18.0 ],
					"numinlets" : 1,
					"items" : [ "baud", 9600, ",", "baud", 19200, ",", "baud", 115200 ],
					"fontname" : "Arial",
					"numoutlets" : 3,
					"id" : "obj-25",
					"outlettype" : [ "int", "", "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "umenu",
					"fontsize" : 10.0,
					"types" : [  ],
					"patching_rect" : [ 279.0, 156.0, 92.0, 18.0 ],
					"numinlets" : 1,
					"items" : [ "port", "a", ",", "port", "b", ",", "port", "c", ",", "port", "d", ",", "port", "e", ",", "port", "f", ",", "port", "g", ",", "port", "h", ",", "port", "i" ],
					"fontname" : "Arial",
					"numoutlets" : 3,
					"id" : "obj-3",
					"outlettype" : [ "int", "", "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"patching_rect" : [ 84.0, 77.0, 39.0, 39.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-256",
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "print",
					"fontsize" : 9.0,
					"patching_rect" : [ 261.0, 134.0, 32.0, 15.0 ],
					"numinlets" : 2,
					"fontname" : "Arial",
					"numoutlets" : 1,
					"id" : "obj-253",
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "99",
					"fontsize" : 9.0,
					"patching_rect" : [ 221.0, 134.0, 32.5, 15.0 ],
					"numinlets" : 2,
					"fontname" : "Arial",
					"numoutlets" : 1,
					"id" : "obj-230",
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"patching_rect" : [ 166.0, 78.0, 22.0, 22.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-228",
					"outlettype" : [ "int" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "metro 10",
					"fontsize" : 9.0,
					"patching_rect" : [ 166.0, 106.0, 46.0, 17.0 ],
					"numinlets" : 2,
					"fontname" : "Arial",
					"numoutlets" : 1,
					"id" : "obj-229",
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "serial i 9600",
					"fontsize" : 11.595187,
					"patching_rect" : [ 166.0, 173.0, 73.0, 20.0 ],
					"numinlets" : 1,
					"fontname" : "Arial",
					"numoutlets" : 2,
					"id" : "obj-226",
					"outlettype" : [ "int", "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "zl group 30",
					"fontsize" : 9.0,
					"patching_rect" : [ 166.0, 221.0, 61.0, 17.0 ],
					"numinlets" : 2,
					"fontname" : "Arial",
					"numoutlets" : 2,
					"id" : "obj-251",
					"outlettype" : [ "", "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "sel 10",
					"fontsize" : 9.0,
					"patching_rect" : [ 166.0, 199.0, 35.0, 17.0 ],
					"numinlets" : 2,
					"fontname" : "Arial",
					"numoutlets" : 2,
					"id" : "obj-254",
					"outlettype" : [ "bang", "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "press 99 couple of times to start communication",
					"linecount" : 3,
					"fontsize" : 9.0,
					"patching_rect" : [ 225.0, 88.0, 100.0, 38.0 ],
					"numinlets" : 1,
					"fontname" : "Arial",
					"numoutlets" : 0,
					"id" : "obj-259"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-5", 6 ],
					"destination" : [ "obj-17", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-226", 0 ],
					"destination" : [ "obj-254", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-226", 0 ],
					"destination" : [ "obj-256", 0 ],
					"hidden" : 0,
					"midpoints" : [ 175.5, 193.0, 161.0, 193.0, 161.0, 133.0, 134.0, 133.0, 134.0, 64.0, 93.5, 64.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-229", 0 ],
					"destination" : [ "obj-226", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-253", 0 ],
					"destination" : [ "obj-226", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-230", 0 ],
					"destination" : [ "obj-226", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 1 ],
					"destination" : [ "obj-226", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 1 ],
					"destination" : [ "obj-226", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 4 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 2 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-5", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 0 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-228", 0 ],
					"destination" : [ "obj-229", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-254", 1 ],
					"destination" : [ "obj-251", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-254", 0 ],
					"destination" : [ "obj-251", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-251", 0 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
