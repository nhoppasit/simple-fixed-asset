USE [DB_FIXED_ASSET]
GO

DECLARE	@return_value int,
		@RowCount int,
		@MessageResult nvarchar(100)

EXEC	@return_value = [dbo].[Sp_Asset_Save]
		@RoomCode = NULL,
		@Epc = NULL,
		@Tid = '343',
		@Fid = '',
		@AssetLabel = NULL,
		@AssetType = NULL,
		@AssetDescription = NULL,
		@SystemId = 1,
		@RowCount = @RowCount OUTPUT,
		@MessageResult = @MessageResult OUTPUT

SELECT	@RowCount as N'@RowCount',
		@MessageResult as N'@MessageResult'

SELECT	'Return Value' = @return_value

select * from TB_ASSET

GO
