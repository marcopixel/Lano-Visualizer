function Initialize()
	local meterFile = io.open(SKIN:GetVariable('@')..'include\\MeterBars.inc','w')
	local barCount = tonumber(SKIN:GetVariable('BarCount'))
	local height = tonumber(SKIN:GetVariable('BarHeight'))
	local width = tonumber(SKIN:GetVariable('BarWidth'))
	local gap = tonumber(SKIN:GetVariable('BarGap'))
	local realWidth = width + gap
	local degree = tonumber(SKIN:GetVariable('degree'))

	local sinAmount = math.sin(math.rad(degree))
	local cosAmount = math.cos(math.rad(degree))
	local shapeX = 0
	if degree > 90 then
		shapeX = -realWidth * barCount * cosAmount

		if degree > 180 then
			shapeX = shapeX - height * sinAmount

			if degree > 270 then
				shapeX = shapeX + realWidth * barCount * cosAmount
			end
		end
	end

	local shapeY = degree ~= 0 and (-height * sinAmount + height * cosAmount) or (-height * sinAmount)
	if degree > 90 then
		shapeY = shapeY - height * cosAmount

		if degree >= 180 then
			shapeY =  height * sinAmount - (realWidth * barCount + width) * sinAmount

			if degree > 270 then
				shapeY =  shapeY - (realWidth * barCount + width) /2  * sinAmount
			end
		end
	else
		shapeY = height * cosAmount
	end

	meterFile:write('[MeterBar]\n'
					,'Meter=Shape\n'
					,'X='..(shapeX-realWidth)..'\n'
					,'Y='..(shapeY-height)..'\n'
					,'Group=GroupBars | GroupDynamicColors\n'
					,'Trait=Fill Color #Color# | StrokeWidth 0\n'
					,'DynamicVariables=1\n')

for i=1,barCount do
        local barX = realWidth * i * cosAmount
        local barY = height + realWidth * i * sinAmount
        local barHeight = width - height
        if i == barCount then X1,Y1 = barX, barY end
        meterFile:write('Shape'..(i == 1 and '' or i)..'= Rectangle '..barX..','..barY..','..width..',('..barHeight..'*([MeasureAudioSmoothed'..i..']>1?1:[MeasureAudioSmoothed'..i..'])-'..width..'),'..(width/2)..' | rotate '..degree..','..(width/2)..',('..-barHeight..'*([MeasureAudioSmoothed'..i..']>1?1:[MeasureAudioSmoothed'..i..'])+'..width..') | Extend Trait\n')

    end
    meterFile:write('Shape'..(barCount+1)..'=Line '..X1..','..Y1..','..(X1+(width+height)*sinAmount)..','..(Y1-(width+height)*cosAmount)..' | StrokeWidth 0 | StrokeColor 0,0,0,0')
    meterFile:close()
end
--[MeasureAudioSmoothed'..i..']
