USE [DB_FIXED_ASSET]
GO
/****** Object:  StoredProcedure [dbo].[Sp_Asset_SearchByTid]    Script Date: 05-Feb-19 3:32:45 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
ALTER PROCEDURE [dbo].[Sp_Asset_SearchByTid]
	-- Add the parameters for the stored procedure here
	@TID nvarchar(50),
	@RowCount int output,
	@MessageResult nvarchar(200) OUTPUT
AS
BEGIN			
	-- ===================================================================================
	-- STATE-1: VALIDATION
	-- ===================================================================================	
	-- tid
	IF @TID is NULL
	begin
		print 'Invalid TID! TID cannot be null.';
		-- THROW 50031, 'Invalid TID! TID can not be NULL.', 1;  
		set @RowCount=0;
		set @MessageResult = 'Invalid TID! TID cannot be null.';
		return -2;
	end
	-- empty
	IF @TID = ''
	begin
		print 'Invalid TID! TID cannot be empty.';
		-- THROW 50031, 'Invalid TID! TID can not be NULL.', 1;  
		set @RowCount=0;
		set @MessageResult = 'Invalid TID! TID cannot be empty.';
		return -2;
	end

	Declare @Id_room int = null;
	select top 1 @Id_room = T.ID from TB_ROOM T WHERE T.ROOM_TID = @Tid; -- CHECK EXIST TID
	if @Id_room is not null or @Id_room <> 0
	begin
				print 'TID is duplicate in ROOM.'
				set @RowCount=0;
				set @MessageResult = 'TID is duplicate in ROOM.';
				return -2;
	end
	-- ===================================================================================
	-- STATE-2: QUERY FROM DATABASE
	-- ===================================================================================
	PRINT 'TID = ' + + RTRIM(CAST(@TID AS nvarchar(50)))
	print 'SELECT and join data from TB_ASSET, TB_ROOM and TB_ASSET_TYPE'

	BEGIN TRY

		SELECT  T1.ID, T1.ASSET_TID , T1.ROOM_CODE, T1.ASSET_EPC, T1.ASSET_FID, T1.ASSET_LABEL, T1.ASSET_TYPE, T1.ASSET_DESCRIPTION,
		  T2.ROOM_TID, T2.ROOM_EPC, T2.ROOM_DESCRIPTION
		from TB_ASSET T1
		LEFT JOIN TB_ROOM T2
		ON T1.ROOM_CODE=T2.ROOM_CODE
		WHERE T1.ASSET_TID=@TID;
						
		SET @RowCount = @@ROWCOUNT;
			
		print 'Done selection'
		IF @RowCount>0 -- data found.
		BEGIN
			SET @MessageResult = 'Asset found.';
			return 0
		END
		ELSE -- data not found!
		BEGIN
			SET @MessageResult = 'Asset not found!';
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
