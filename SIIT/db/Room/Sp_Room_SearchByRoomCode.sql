USE [DB_FIXED_ASSET]
GO
/****** Object:  StoredProcedure [dbo].[Sp_Room_SearchByRoomCode]    Script Date: 05-Feb-19 4:01:14 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
ALTER PROCEDURE [dbo].[Sp_Room_SearchByRoomCode]
	-- Add the parameters for the stored procedure here
	@RoomCode nvarchar(50),
	@RowCount int output,
	@MessageResult nvarchar(200) OUTPUT
AS
BEGIN			
	-- ===================================================================================
	-- STATE-1: VALIDATION
	-- ===================================================================================	
	-- fid
	IF @RoomCode is NULL
	begin
		print 'Invalid Room Code! Room Code cannot be null.';
		-- THROW 50031, 'Invalid Room Code! Room Code can not be NULL.', 1;  
		set @RowCount=0;
		set @MessageResult = 'Invalid Room Code! Room Code cannot be null.';
		return -2;
	end
	IF @RoomCode = ''
	begin
		print 'Invalid Room Code! Room Code cannot be empty.';
		-- THROW 50031, 'Invalid Room Code! Room Code can not be NULL.', 1;  
		set @RowCount=0;
		set @MessageResult = 'Invalid Room Code! Room Code cannot be empty.';
		return -2;
	end

	-- ===================================================================================
	-- STATE-2: QUERY FROM DATABASE
	-- ===================================================================================
	PRINT 'Room Code = ' + + RTRIM(CAST(@RoomCode AS nvarchar(50)))
	print 'SELECT and join data from TB_ROOM'

	BEGIN TRY

		SELECT   T1.ID, T1.ROOM_CODE, T1.ROOM_TID, T1.ROOM_EPC, T1.ROOM_DESCRIPTION,
		 T2.ASSET_TID , T2.ASSET_EPC, T2.ASSET_FID, T2.ASSET_LABEL, T2.ASSET_TYPE, T2.ASSET_DESCRIPTION
		from  TB_ROOM T1
		LEFT JOIN TB_ASSET T2
		ON T1.ROOM_CODE = T2.ROOM_CODE
		WHERE T1.ROOM_CODE = @RoomCode;
						
		SET @RowCount = @@ROWCOUNT;
			
		print 'Done selection'
		IF @RowCount>0 -- data found.
		BEGIN
			SET @MessageResult = 'Room found.';
			return 0
		END
		ELSE -- data not found!
		BEGIN
			SET @MessageResult = 'Room not found!';
			return -1
		END

	END TRY
	BEGIN CATCH
		print 'QUERY ERROR'
		SET @RowCount = 0;
		SET @MessageResult = ERROR_MESSAGE();
		return -2
	END CATCH

	-- SAFETY
	return -99

-- END OF STORE PROCEDURE.
END
