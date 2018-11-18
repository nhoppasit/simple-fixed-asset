USE [DB_FIXED_ASSET]
GO
/****** Object:  StoredProcedure [dbo].[Sp_PreparingArea_Save]    Script Date: 9/17/2018 11:30:27 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
alter PROCEDURE [dbo].[Sp_Asset_Save] -- !!! สำคัญ ต้องเปลี่ยน Activity type
	@RoomCode nvarchar(50),	
	@Epc nvarchar(50),	
	@Tid nvarchar(50),	
	@Fid nvarchar(50),	
	@AssetLabel nvarchar(200),	
	@AssetType nvarchar(200),	
	@AssetDescription nvarchar(1000),	
	@SystemId int,
	@RowCount int output,
	@MessageResult nvarchar(100) output
AS
BEGIN

	-- ===================================================================================
	-- STATE-1: VALIDATION
	--             - CHECK NULL
	--             - CHECK EMPTY
	-- ===================================================================================
	-- System id
	IF @SystemId is NULL
	begin
		set @RowCount = 0;
		set @MessageResult = 'Invalid system id! System id cannot be null.';
		return -2;
	end	
	IF @SystemId<=0
	begin
		set @RowCount = 0;
		set @MessageResult = 'Invalid system id! system id must more than 0.';
		return -2;
	end	
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
	select top 1 @Id = T.ID from TB_ASSET T WHERE T.TID = @Tid; -- CHECK EXIST TID

	if @Id is null or @Id=0 /* CRITERIA FOR INSERT NEW*/
	begin
		
		begin try
				
			-- DO INSERT
			print 'INSERTION AS NEW RECORD...'

			INSERT INTO TB_ASSET
			(
				ROOM_CODE,
				EPC,
				TID,
				FID,
				ASSET_LABEL,
				ASSET_TYPE,
				ASSET_DESCRIPTION,
				CREATED_DATE,
				CREATED_BY,
				MODIFIED_DATE,
				MODIFIED_BY
			) 
			VALUES 
			(
				@RoomCode,
				@Epc,
				@Tid,
				@Fid,
				@AssetLabel,
				@AssetType,
				@AssetDescription,
				getdate(),
				@SystemId,
				getdate(),
				@SystemId
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
				EPC = @Epc,
				FID = @Fid,
				ASSET_LABEL = @AssetLabel,
				ASSET_TYPE = @AssetType,
				ASSET_DESCRIPTION = @AssetDescription,
				MODIFIED_DATE = GETDATE(),
				MODIFIED_BY = @SystemId
			where TID=@Tid;

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
