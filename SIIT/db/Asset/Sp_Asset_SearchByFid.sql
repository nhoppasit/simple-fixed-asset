USE [DB_FIXED_ASSET]
GO
/****** Object:  StoredProcedure [dbo].[Sp_Asset_SearchByFid]    Script Date: 05-Feb-19 3:32:02 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
ALTER PROCEDURE [dbo].[Sp_Asset_SearchByFid]
	-- Add the parameters for the stored procedure here
	@FID nvarchar(50),
	@RowCount int output,
	@MessageResult nvarchar(200) OUTPUT
AS
BEGIN			
	-- ===================================================================================
	-- STATE-1: VALIDATION
	-- ===================================================================================	
	-- fid
	IF @FID is NULL
	begin
		print 'Invalid TID! TID cannot be null.';
		-- THROW 50031, 'Invalid TID! TID can not be NULL.', 1;  
		set @RowCount=0;
		set @MessageResult = 'Invalid TID! TID cannot be null.';
		return -2;
	end
	IF @FID = ''
	begin
		print 'Invalid TID! TID cannot be empty.';
		-- THROW 50031, 'Invalid TID! TID can not be NULL.', 1;  
		set @RowCount=0;
		set @MessageResult = 'Invalid TID! TID cannot be empty.';
		return -2;
	end

	-- ===================================================================================
	-- STATE-2: QUERY FROM DATABASE
	-- ===================================================================================
	PRINT 'TID = ' + + RTRIM(CAST(@FID AS nvarchar(50)))
	print 'SELECT and join data from TB_ASSET, TB_ROOM and TB_ASSET_TYPE'

	BEGIN TRY

		SELECT  T1.ID, T1.ASSET_TID , T1.ROOM_CODE, T1.ASSET_EPC, T1.ASSET_FID, T1.ASSET_LABEL, T1.ASSET_TYPE, T1.ASSET_DESCRIPTION,
		  T2.ROOM_TID, T2.ROOM_EPC, T2.ROOM_DESCRIPTION		from TB_ASSET T1
		LEFT JOIN TB_ROOM T2
		ON T1.ROOM_CODE=T2.ROOM_CODE
		WHERE T1.ASSET_FID=@FID;
						
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
