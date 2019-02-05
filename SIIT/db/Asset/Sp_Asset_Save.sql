USE [DB_FIXED_ASSET]
GO
/****** Object:  StoredProcedure [dbo].[Sp_Asset_Save]    Script Date: 05-Feb-19 4:00:03 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
ALTER PROCEDURE [dbo].[Sp_Asset_Save] -- !!! สำคัญ ต้องเปลี่ยน Activity type
	@RoomCode nvarchar(50),	
	@Epc nvarchar(50),	
	@Tid nvarchar(50),	
	@Fid nvarchar(50),	
	@AssetLabel nvarchar(200),	
	@AssetType nvarchar(200),	
	@AssetDescription nvarchar(1000),	
	@RowCount int output,
	@MessageResult nvarchar(100) output
AS
BEGIN

	-- ===================================================================================
	-- STATE-1: VALIDATION
	--             - CHECK NULL
	--             - CHECK EMPTY
	-- ===================================================================================
	
	-- TID
	IF @Tid is NULL
	begin
		set @RowCount = 0;
		set @MessageResult = 'Invalid TID! TID cannot be null.';
		return -2;
	end	
	IF @Tid=''
	begin
		set @RowCount = 0;
		set @MessageResult = 'Invalid TID! TID cannot be empty.';
		return -2;
	end	
	-- FID
	IF @Fid is NULL
	begin
		set @RowCount = 0;
		set @MessageResult = 'Invalid FID! FID cannot be null.';
		return -2;
	end	
	IF @Fid=''
	begin
		set @RowCount = 0;
		set @MessageResult = 'Invalid FID! FID cannot be empty.';
		return -2;
	end	

	-- ===================================================================================
	-- STATE-2: SAVE BY INSERT OR UPDATE
	-- ===================================================================================	
	Declare @Id int = null;
	select top 1 @Id = T.ID from TB_ASSET T WHERE T.ASSET_TID = @Tid; -- CHECK EXIST TID

	if @Id is null or @Id=0 /* CRITERIA FOR INSERT NEW*/
	begin
		
		begin try
				
			-- DO INSERT
			print 'INSERTION AS NEW RECORD...'

			INSERT INTO TB_ASSET
			(
				ROOM_CODE,
				ASSET_EPC,
				ASSET_TID,
				ASSET_FID,
				ASSET_LABEL,
				ASSET_TYPE,
				ASSET_DESCRIPTION				
			) 
			VALUES 
			(
				@RoomCode,
				@Epc,
				@Tid,
				@Fid,
				@AssetLabel,
				@AssetType,
				@AssetDescription
			)
			
			set @RowCount = @@ROWCOUNT;
			
			-- RETURN
			IF @RowCount>0 -- INSERTION SUCCESS
			BEGIN
				print 'INSERTION SUCCESS.'
				set @MessageResult = 'Insertion a new asset success.';
				return 0;
			END
			ELSE -- NOTHING
			BEGIN
				print 'INSERTION NOTHING'
				set @MessageResult = 'There is no any save activity.';
				return -1;
			END
		end try
		begin catch
			set @RowCount = 0;
			set @MessageResult = ERROR_MESSAGE();
			return -2;
		end catch
		
	END
	else -- do update the asset recode by TID
	begin
		
		begin try

			print 'UPDATING...'
			
			update TB_ASSET
			set 
				ROOM_CODE = @RoomCode,
				ASSET_EPC = @Epc,
				ASSET_FID = @Fid,
				ASSET_LABEL = @AssetLabel,
				ASSET_TYPE = @AssetType,
				ASSET_DESCRIPTION = @AssetDescription
			where ASSET_TID=@Tid;

			set @RowCount=@@ROWCOUNT;

			-- RETURN
			IF @RowCount>0 -- UPDATED
			BEGIN
				PRINT 'UPDATING SUCCESS';
				set @MessageResult = 'Asset data updated successful.';
				return 0
			END
			ELSE -- NOTHING
			BEGIN
				PRINT 'Nothing updated';
				set @MessageResult = 'There is no any save activity.';
				return -1
			END

		end try
		begin catch
			set @RowCount = 0;
			set @MessageResult = ERROR_MESSAGE();
			return -2;
		end catch

	end

	-- safety
	return -99;

/* END */
END
